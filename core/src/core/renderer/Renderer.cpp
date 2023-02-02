#include "_Core.h"

#include "renderer/Renderer.h"
#include "component/SpriteRenderer.h"
#include "generic/Application.h"

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
            RenderBatch* newBatch = new RenderBatch(MAX_BATCH_SIZE, index, core::GameObject::CGMap[spriteRenderer]->displayMode);
            newBatch->start();
            batches.push_back(newBatch);
            newBatch->addSprite(spriteRenderer);
            std::sort(batches.begin(), batches.end(), less_than_key());
        }
    }

    void Renderer::render(LayerStack& layer_stack, const float dt) {
        if (Application::GetImGuiEnabled())
			frame_buffer->Bind();
        else
            glViewport(0, 0, Application::getWindow()->getWidth(), Application::getWindow()->getHeight());

        //calculating camera vectors
        Application::getCurrentScene()->getCamera()->calcCameraVectors();

        //update GameObjects
        updateGameObjects(dt, Application::getCurrentScene()->gameObjects);

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

        frame_buffer->Unbind();
    }

    void Renderer::updateGameObjects(float dt, std::vector<GameObject*>& gameObjects)
    {
        // update the gameObjects so it displays the changes

        for (Layer* layer : Application::GetLayerStack())
        {
            for (GameObject* game_object : layer->GetGameObjects())
            {
                game_object->update(dt);
            }
        }
    }
}
