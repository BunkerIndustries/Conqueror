#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Component.h"

namespace core
{
	class SpriteSheet : public Component
	{
    public:
        SpriteSheet(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, glm::vec2 selectedSprite);
        SpriteSheet(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite);

        void Init(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite);

        void OnStart() override { }
        void OnStop() override { }
        void OnUpdate() override;
        void OnImgui(float dt) override;
        void OnEvent(Event& event) override { }

        int GetSpriteCount() { return spriteRows + spriteColumns; };
        int GetSpriteRows() { return spriteRows; };
        int GetSpriteColumns() { return spriteColumns; };

        void ChangeSprite(glm::vec2 pos);

        void ChangeCoords();

    private:
        glm::vec4 color;
        Shr<Texture> texture;

        glm::vec2 texCoords[4];

        float spriteWidth;
        float spriteHeight;

        float paddingWidth;
        float paddingHeight;

        float textureWidth;
        float textureHeight;

        int spriteRows;
        int spriteColumns;

        glm::vec2 selectedSprite;
	};
};