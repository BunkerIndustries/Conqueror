#include "_Game.h"
#include "SingleAnimationComponent.h"

SingleAnimation::SingleAnimation(Shr<Texture> animation, float animSpriteWidth, float animSpriteHeight, float animPaddingWidth, float animPaddingHeight, glm::vec2 indexStart, glm::vec2 indexEnd, int animationSpeed, glm::vec2 standartIndex, Shr<Texture> standart, float standartSpriteWidth, float standartSpriteHeight, float standartPaddingWidth, float standartPaddingHeight)//use if object has only one possible animation cycle
	: animation(animation), animSpriteWidth(animSpriteWidth), animSpriteHeight(animSpriteHeight), animPaddingWidth(animPaddingWidth), animPaddingHeight(animPaddingHeight), indexStart(indexStart), indexEnd(indexEnd), animationSpeed(animationSpeed), standartIndex(standartIndex), standart(standart), standartSpriteWidth(standartSpriteWidth), standartSpriteHeight(standartSpriteHeight), standartPaddingWidth(standartPaddingWidth), standartPaddingHeight(standartPaddingHeight) {}
	


void SingleAnimation::PlayAnimation() {
    gameObject->RemoveComponent<SpriteSheet>();
    gameObject->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), animation, animSpriteWidth, animSpriteHeight, animPaddingWidth, animPaddingHeight, glm::vec2(0.0f, 0.0f)));
    int animationLength = indexEnd.x - indexStart.x + 1;
    static int tex = 0;
    static float x = 0.01f;
    x += Application::GetDT() / animationSpeed;

    tex = (int)(x * 100);

    if (tex % (animationLength + 1) == 0)
    {
        x = 0.01f;
        tex = (int)(x * 100);
    }
    gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(tex + indexStart.x -1, indexStart.y));
}

void SingleAnimation::StopAnimation() {
    LOG_DEBUG(animation);
    LOG_DEBUG(standart);
    gameObject->RemoveComponent<SpriteSheet>();
    gameObject->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), standart, standartSpriteWidth, standartSpriteHeight, standartPaddingWidth, standartPaddingHeight, glm::vec2(0.0f, 0.0f)));
    gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(standartIndex.x, standartIndex.y));
}