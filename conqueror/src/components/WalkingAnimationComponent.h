#pragma once
#include "Engine.h"

class WalkingAnimation : public Component {
public:
	WalkingAnimation();
	WalkingAnimation(glm::ivec2 indexStartUp, glm::ivec2 IndexEndUp, glm::ivec2 IndexStartDown, glm::ivec2 indexEndDown, glm::ivec2 indexStartRight, glm::ivec2 IndexEndRight, glm::ivec2 IndexStartLeft, glm::ivec2 indexEndLeft, int animationSpeed, int spriteSheetLength);
	void OnStart() override { }
	void OnStop() override { }
	void OnUpdate() override;
	void OnEvent(Event& event) override {};
	std::string CalculateDirection();
	void Start(glm::ivec2 indexStart, glm::ivec2 indexEnd);


private:
	int max;
	int animationSpeed;
	int spriteSheetLength;
	glm::ivec2 indexStart;
	glm::ivec2 indexEnd;
	glm::ivec2 indexStartUp;
	glm::ivec2 indexEndUp;
	glm::ivec2 indexStartDown;
	glm::ivec2 indexEndDown;
	glm::ivec2 indexStartLeft;
	glm::ivec2 indexEndLeft;
	glm::ivec2 indexStartRight;
	glm::ivec2 indexEndRight;
};