#pragma once
#include "Engine.h"

class SingleAnimation : public Component {
public:
	SingleAnimation(Shr<Texture> animation, float animSpriteWidth, float animSpriteHeight, float animPaddingWidth, float animPaddingHeight, glm::vec2 indexStart, glm::vec2 indexEnd, int animationSpeed, glm::vec2 standartIndex, Shr<Texture> standart, float standartSpriteWidth, float standartSpriteHeight, float standartPaddingWidth, float standartPaddingHeight);
	void OnStart() override { }
	void OnStop() override { }
	void OnEvent(Event& event) override {};
	void OnUpdate() override {}
	void PlayAnimation();
	void StopAnimation();
private:
	Shr<Texture> animation;
	float animSpriteWidth;
	float animSpriteHeight;
	float animPaddingWidth;
	float animPaddingHeight;
	glm::vec2 indexStart;
	glm::vec2 indexEnd;
	int animationSpeed;
	glm::vec2 standartIndex;
	Shr<Texture> standart;
	float standartSpriteWidth;
	float standartSpriteHeight;
	float standartPaddingWidth;
	float standartPaddingHeight;
};