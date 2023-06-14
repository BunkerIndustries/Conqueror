#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Component.h"
#include "component/Sprite.h"

namespace core
{
    class SpriteSheet : public Component
    {
    public:
        SpriteSheet(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite, bool registerAlphaPixelsToEvent = false);

        void Init(Shr<Texture> texture, glm::vec2 selectedSprite);

        void OnStart() override { }
        void OnStop() override { }
        void OnUpdate() override;
        void OnImgui(float dt) override;
        void OnEvent(Event& event) override { }

        int GetSpriteCount() { return spriteRows + spriteColumns; };
        int GetSpriteRows() { return spriteRows; };
        int GetSpriteColumns() { return spriteColumns; };

        void ChangeSprite(glm::vec2 pos);
        void ChangeColor(glm::vec4 newColor);


    private:
        glm::vec4 color;
        Shr<Texture> texture;

        std::array<glm::vec2, 4> texCoords;

        float spriteWidth;
        float spriteHeight;

        float paddingWidth;
        float paddingHeight;

        float textureWidth;
        float textureHeight;

        int spriteRows;
        int spriteColumns;

        glm::vec2 selectedSprite;

        bool registerAlphaPixelsToEvent;

        std::vector<std::vector<Shr<Sprite>>> Sprites;

        void ChangeCoords();
    };
};