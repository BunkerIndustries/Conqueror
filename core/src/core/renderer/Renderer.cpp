#include "_Core.h"

#include "renderer/Renderer.h"
#include "component/SpriteRenderer.h"
#include "generic/Application.h"
#include "event/Input.h"
#include "event/MouseCodes.h"
#include "event/GameEvent.h"

#include "glad/glad.h"
namespace core {

    Renderer* Renderer::instance;

    struct less_than_key
    {
        inline bool operator() (RenderBatch* batch1, RenderBatch* batch2)
        {
            return (batch1->getZIndex() < batch2->getZIndex());
        }
    };

    Renderer::Renderer() {
        instance = this;
        FramebufferAttachSpecification attach = { FramebufferTexFormat::RGBA8, FramebufferTexFormat::RED_INTEGER, FramebufferTexFormat::DEPTH24STECIL8 };
        properties.attachment = attach;
        properties.width = 1080;
        properties.height = 720;
        frame_buffer = new FrameBuffer(properties);
    }

    Renderer::~Renderer() {

    }

    void Renderer::add(Layer* layer, int index) {
        for (GameObject* game_object : layer->GetGameObjects()) {
            // create spriterenderer with the coponent spriterneder if a spriterenderer exists
            SpriteRenderer* spriteRenderer = (SpriteRenderer*)game_object->getComponent(std::string("sprite_renderer"));
            if (spriteRenderer != nullptr) {
                add(spriteRenderer, index);
            }
        }
    }

    void Renderer::add(SpriteRenderer* spriteRenderer, int index) {
        // add sprite to current batch if the batch has room for it and the ZIndex fits accordingly (if it is equal to both of the Zindex's (just for security))
        // do this for every other spriterenderer
        bool added = false;
        bool found = false;
        for (RenderBatch* batch : batches)
        {
            found = batch->hasSprite(spriteRenderer);
        }
        for (int i = 0; !found && i < batches.size(); i++) {
            
            if (batches[i]->hasRoom() && index == batches[i]->getZIndex())
            {
                std::shared_ptr<Texture> texture = spriteRenderer->getTexture();
                if (texture == nullptr || (batches[i]->hasTexture(texture) || batches[i]->hasTextureRoom()))
                {
                    batches[i]->addSprite(spriteRenderer);
                    added = true;
                    break;
                }
            }
        }
        if (!added && !found) {
            // if there is no place for the spriterenderer, create a new renderbatch with the needed setup (functions)
            RenderBatch* newBatch = new RenderBatch(MAX_BATCH_SIZE, index, spriteRenderer->GetGameObject()->displayMode);
            newBatch->start();
            batches.push_back(newBatch);
            newBatch->addSprite(spriteRenderer);
            std::sort(batches.begin(), batches.end(), less_than_key());
        }
    }

    void Renderer::render(const float dt) {
        frame_buffer->Bind();
        if (!Application::GetImGuiEnabled())
        {
            if (frame_buffer->GetProperties().width != Application::GetWindow()->getWidth() || frame_buffer->GetProperties().height != Application::GetWindow()->getHeight())
            {
                frame_buffer->Resize(Application::GetWindow()->getWidth(), Application::GetWindow()->getHeight());
            }
            glViewport(0, 0, Application::GetWindow()->getWidth(), Application::GetWindow()->getHeight());
        }

        //calculating camera vectors
        Application::GetCurrentScene()->getCamera()->calcCameraVectors();

        //update GameObjects
        updateGameObjects(dt);

        //clear core id attachment to -1
        frame_buffer->ClearAttachment(1, -1);

        int sprites_count_calc = 0;
        int vertices_count_calc = 0;
        // render all batches
        for (int i = 0; i < batches.size(); i++) {
            sprites_count_calc += batches[i]->GetSpritesCount();
            vertices_count_calc += batches[i]->GetVertexCount();
            batches[i]->render();
        }

        sprites_count = sprites_count_calc;
        vertex_count = vertices_count_calc;

        //IMGUI window panel for framebuffer picture
        if (!Application::GetImGuiEnabled()) {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            window_flags |= ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;// | ImGuiWindowFlags_MenuBar;
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            ImGuiViewport& viewport = *ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport.Pos);
            ImGui::SetNextWindowSize(viewport.Size);
            ImGui::SetNextWindowViewport(viewport.ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

            ImGui::Begin(" ", nullptr, window_flags);
            ImGui::PopStyleVar(3);

            ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
            if (viewportSize != *(glm::vec2*)&viewport_panel_size)
            {
                viewportSize = { viewport_panel_size.x, viewport_panel_size.y };
                Application::GetCurrentScene()->GetRenderer().GetFrameBuffer().Resize(viewportSize.x, viewportSize.y);
            }
            uint32_t textureID = Application::GetCurrentScene()->GetRenderer().GetFrameBuffer().GetColorID(0);

            ImGui::Image((void*)textureID, ImVec2(viewportSize.x, viewportSize.y), ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
            ImGui::End();
        }

        //mouse picking;
        glm::ivec2 pos = glm::ivec2(-1, -1);

        if (!Application::GetImGuiEnabled())
        {
            glm::vec2 mousePos = Input::GetMousPos();

            mousePos.y = Application::GetWindow()->getHeight() - mousePos.y;
            if (mousePos.x < Application::GetWindow()->getWidth() && mousePos.y < Application::GetWindow()->getHeight())
            {
                pos = mousePos;
            }

        }
        else if (Application::GetImGuiLayer().IsMouseInsideViewport())
        {
            pos = Application::GetImGuiLayer().GetMousePosViewportRelative();
        }

        if (pos.x >= 0 && pos.y >= 0) {
            mouseHoverID[0] = frame_buffer->ReadPixel(1, pos);
        }

        if (Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouseClickedID[0] = mouseHoverID[0];
            if (mouseClickedID[0] != mouseClickedID[1] && mouseClickedID[0] != -1 && !pressed) 
            {
                Application::QueueEvents(new GameObjectPressedEvent(GameObject::GetGameObjectByID(mouseClickedID[0])));
            }
            pressed = true;
            mouseClickedID[1] = mouseClickedID[0];
        }
        else {
            pressed = false;
            if (mouseClickedID[1] != -1) {
                Application::QueueEvents(new GameObjectReleasedEvent(GameObject::GetGameObjectByID(mouseClickedID[1])));
            }


            mouseClickedID[1] = -1;
            if (mouseHoverID[0] != mouseHoverID[1])
            {
                
                if (mouseHoverID[1] != -1) {
                    Application::QueueEvents(new GameObjectHoverEndEvent(GameObject::GetGameObjectByID(mouseHoverID[1])));
                }
                if (mouseHoverID[0] != -1) {
                    Application::QueueEvents(new GameObjectHoverBeginEvent(GameObject::GetGameObjectByID(mouseHoverID[0])));
                }
					
            }
            else if (mouseHoverID[0] != mouseHoverID[1] && mouseHoverID[0] == -1)
            {
            }
            mouseHoverID[1] = mouseHoverID[0];
        }


        frame_buffer->Unbind();
    }

    void Renderer::updateGameObjects(float dt)
    {
        // update the gameObjects so it displays the changes

        for (Layer* layer : Application::GetLayerStack())
        {
            for (GameObject* game_object : layer->GetGameObjects())
            {
                if (!game_object->IsRunning()) continue;
                game_object->update(dt);
            }
        }
    }
}
