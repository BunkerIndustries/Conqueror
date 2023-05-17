#pragma once
#include "Engine.h"
#include "component/SpriteSheet.h"


class SingleAnimation : public Component {
public:
	SingleAnimation(Shr<Texture> animation, float animSpriteWidth, float animSpriteHeight, float animPaddingWidth, float animPaddingHeight, glm::vec2 indexStart, glm::vec2 indexEnd, int animationSpeed, glm::vec2 standartIndex, Shr<Texture> standart, float standartSpriteWidth, float standartSpriteHeight, float standartPaddingWidth, float standartPaddingHeight);
	void OnStart() override { }
	void OnStop() override { }
	void OnUpdate() override;
	void OnEvent(Event& event) override {};
	void PlayAnimation();
	void StopAnimation();
private:
	glm::vec2 indexStart;
	glm::vec2 indexEnd;
	int animationSpeed;
	glm::vec2 standartIndex;
	bool play;
	Shr<Texture> animation;
	Shr<Texture> standart;
	float animSpriteWidth;
	float animSpriteHeight;
	float animPaddingWidth;
	float animPaddingHeight;
	float standartSpriteWidth;
	float standartSpriteHeight;
	float standartPaddingWidth;
	float standartPaddingHeight;
};