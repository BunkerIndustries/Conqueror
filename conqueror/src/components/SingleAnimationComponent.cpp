#include "_Game.h"
#include "SingleAnimationComponent.h"

SingleAnimation::SingleAnimation(Shr<Texture> animation, float animSpriteWidth, float animSpriteHeight, float animPaddingWidth, float animPaddingHeight, glm::vec2 indexStart, glm::vec2 indexEnd, float animationSpeed, glm::vec2 standartIndex, Shr<Texture> standart, float standartSpriteWidth, float standartSpriteHeight, float standartPaddingWidth, float standartPaddingHeight)//use if object has only one possible animation cycle
	: animation(animation), animSpriteWidth(animSpriteWidth), animSpriteHeight(animSpriteHeight), animPaddingWidth(animPaddingWidth), animPaddingHeight(animPaddingHeight), indexStart(indexStart), indexEnd(indexEnd), animationSpeed(animationSpeed), standartIndex(standartIndex), standart(standart), standartSpriteWidth(standartSpriteWidth), standartSpriteHeight(standartSpriteHeight), standartPaddingWidth(standartPaddingWidth), standartPaddingHeight(standartPaddingHeight) {}
	
void SingleAnimation::OnUpdate() {
    if (oneCycle == true) {
        int animationLength = indexEnd.x - indexStart.x + 1;
        static int tey = 1;
        static float y = 0.01f;
        y += Application::GetDT();
        if (y > animationSpeed) {
            tey += 1;
            y -= animationSpeed;
            gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(tey + indexStart.x - 1, indexStart.y));
        }

        if (tey % (animationLength + 1) == 0)
        {
            oneCycle = false;
            StopAnimation();
            y = 0.0f;
            tey = 1;
        }
    }
}

void SingleAnimation::PlayAnimation(bool onceCycle) {
    gameObject->RemoveComponent<SpriteSheet>();
    gameObject->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), animation, animSpriteWidth, animSpriteHeight, animPaddingWidth, animPaddingHeight, glm::vec2(0.0f, 0.0f)));
    if (onceCycle == true) {
        oneCycle = true;
    }
    else {
        oneCycle = false;
        int animationLength = indexEnd.x - indexStart.x + 1;
        static int tex = 0;
        static float x = 0.01f;
        x += Application::GetDT();
        if (x > animationSpeed) {
            tex += 1;
            x -= animationSpeed;
        }
        if (tex % animationLength == 0)
        {
            tex = 0;
        }
        gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(tex + indexStart.x, indexStart.y));
    }
    
}

void SingleAnimation::StopAnimation() {
    gameObject->RemoveComponent<SpriteSheet>();
    gameObject->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), standart, standartSpriteWidth, standartSpriteHeight, standartPaddingWidth, standartPaddingHeight, glm::vec2(0.0f, 0.0f)));
    gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(standartIndex.x, standartIndex.y));
}