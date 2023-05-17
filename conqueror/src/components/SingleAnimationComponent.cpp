#include "_Game.h"
#include "SingleAnimationComponent.h"
#include "required/functions.h"
#include "required/constants.h"
#include "component/SpriteSheet.h"
SingleAnimation::SingleAnimation(Shr<Texture> animation, float animSpriteWidth, float animSpriteHeight, float animPaddingWidth, float animPaddingHeight, glm::vec2 indexStart, glm::vec2 indexEnd, int animationSpeed, glm::vec2 standartIndex, Shr<Texture> standart, float standartSpriteWidth, float standartSpriteHeight, float standartPaddingWidth, float standartPaddingHeight)
	: animation(animation), animSpriteWidth(animSpriteWidth), animSpriteHeight(animSpriteHeight), animPaddingWidth(animPaddingWidth), animPaddingHeight(animPaddingHeight), indexStart(indexStart), indexEnd(indexEnd), animationSpeed(animationSpeed), standartIndex(standartIndex), standart(standart), standartSpriteWidth(animSpriteWidth), standartSpriteHeight(animSpriteHeight), standartPaddingWidth(animPaddingWidth), standartPaddingHeight(animPaddingHeight) {}

void SingleAnimation::OnUpdate() {

}


void SingleAnimation::PlayAnimation() {
    gameObject->GetComponent<SpriteSheet>()->ChangeSpriteSheet(animation, animSpriteWidth, animSpriteHeight, animPaddingWidth, animPaddingHeight, indexStart);
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
	gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(tex + indexStart.x - 1, indexStart.y));
	
}

void SingleAnimation::StopAnimation() {
    gameObject->GetComponent<SpriteSheet>()->ChangeSpriteSheet(standart, standartSpriteWidth, standartSpriteHeight, standartPaddingWidth, standartPaddingHeight, standartIndex);
}
/*
void SingleAnimation::OnEvent() {

}
*/
