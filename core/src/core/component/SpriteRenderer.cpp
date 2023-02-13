#include "_Core.h"

#include "component/SpriteRenderer.h"
#include "generic/GameObject.h"
#include "renderer/Texture.h"
#include "utils/DataPool.h"
#include "utils/Utils.h"

#include "imgui/ImGuiLayer.h"

namespace core {


    //SPRITERENDERER
    SpriteRenderer::SpriteRenderer(glm::vec4 color)
	    : Component("sprite_renderer")
	{
    	this->color = color;
        isDirty = true;
        // set newest sprite to no texture (symoblizes that this sprite only contains colors and no texture)
        this->sprite = new Sprite(nullptr);
    }

    SpriteRenderer::SpriteRenderer(Sprite* sprite)
	    : Component("sprite_renderer")
    {
    	// our sprite is the sprite from the function call
        this->sprite = sprite;
        // set default colors
        this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        // this signals changes, another functions look out for this, in order to update the sprite
        isDirty = true;
    }


    SpriteRenderer::~SpriteRenderer() {
        // every new keyword requires a 'delete' keyword (free manually allocated pointer)
        delete sprite;
        delete lastTransform;
    }

    void SpriteRenderer::start() {
        // change values from the previous frame in order to check if the gameObject changed values
        // the local lastTransform variable always holds the old values, in order to be compared to the 'new' value
        lastTransform = gameObject->transform.copy();
    }

    void SpriteRenderer::update(float dt) {
        // check if there have been made changes to the sprite (transform of the gameObject)
        if (!(gameObject->transform.equals(*lastTransform)))
        {
            // if it is not equal, save it to the local transform and
            // set the dirty bit (variable that is being checked in order to display changes)
            //core::GameObject::CGMap[this]->transform.copy(*this->lastTransform);
            gameObject->transform.copy(*this->lastTransform);
            isDirty = true;
        }
    }

    static float timeUntilRefresh = 0.0f;
    static std::vector<std::string> texturePaths;

    void SpriteRenderer::imgui(float dt) {
        ImGui::Text("Component - SpriteRenderer:");
        if (this->getTexture() == nullptr) {
            float colorArray[4]{
                    color.x,
                    color.y,
                    color.z,
                    color.w
            };
            ImGui::ColorPicker3("ColorPicker", colorArray, 0);
            if (!(color.x == colorArray[0] && color.y == colorArray[1] && color.z == colorArray[2] && color.w == colorArray[3])) {
                color = glm::vec4(colorArray[0], colorArray[1], colorArray[2], colorArray[3]);
                isDirty = true;
            }
        }
        else {
            timeUntilRefresh -= dt;
            if (timeUntilRefresh <= 0.0f) {
                texturePaths.erase(texturePaths.begin(), texturePaths.end());
                DIR* dir = opendir("assets/textures");
                struct dirent* entity;
                entity = readdir(dir);
                while (entity != NULL) {
                    std::string name = entity->d_name;
                    if (name != "." && name != "..") {
                        texturePaths.insert(texturePaths.end(), entity->d_name);
                    }
                    entity = readdir(dir);
                }
                timeUntilRefresh = 1.0f;
            }
            ImVec2 windowPos = ImGui::GetWindowPos();
            ImVec2 windowSize = ImGui::GetWindowSize();
            float windowX2 = windowPos.x + windowSize.x;
            for (int i = 0; i < texturePaths.size(); i++) {
                std::shared_ptr<Texture> texture = DataPool::getTexture(texturePaths[i]);

                const int IMGSIZE_HEIGHT = 100;
                Utils::XY ratio = Utils::calculateAspectRatioFit(texture->getWidth(), texture->getHeight(), texture->getWidth() + IMGSIZE_HEIGHT, IMGSIZE_HEIGHT);

                ImGui::PushID(i);
                if (ImGui::ImageButton((void*)texture->getID(), ImVec2(ratio.width, ratio.height), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), 2, ImColor(0, 0, 0, 1))) {
                    delete sprite;
                    this->sprite = new Sprite(texture);
                    isDirty = true;
                }
                ImGui::PopID();

                ImVec2 lastButtonPos = ImGui::GetItemRectMax();
                float lastButtonPosX2 = lastButtonPos.x;
                float nextButtonX2 = lastButtonPosX2 + ratio.width + 50.0f;
                if (i + 1 < texturePaths.size() && nextButtonX2 < windowX2) {
                    ImGui::SameLine();
                }
            }
        }
    }

    glm::vec4 SpriteRenderer::getColor() {
        // return current sprite color
        return this->color;
    }

    std::shared_ptr<Texture> SpriteRenderer::getTexture()
    {
        // return current texture that is being used in this sprite
        return sprite->getTexture();
    }

    float* SpriteRenderer::getTexCoords()
    {
        // return the coordinates of the texture that is being used in this sprite
        return this->sprite->getTexCoords();
    }

    void SpriteRenderer::setSprite(Sprite* sprite)
    {
        // set the sprite to the function parameter desired sprite
        this->sprite = sprite;
        // set to true because changes have been made
        isDirty = true;
    }

    void SpriteRenderer::setColor(glm::vec4 color) {
        // set color
        this->color = color;
        delete this->sprite;
        this->sprite = new Sprite(nullptr);
        // set to true because changes have been made
        isDirty = true;
    }

    void SpriteRenderer::setClean()
    {
        // reset sprite changes, this function is being called after it rendered the changes
        // reset function
        isDirty = false;
    }

    bool SpriteRenderer::getIsDirty()
    {
        // get the current state of isDirty
        return isDirty;
    }
}