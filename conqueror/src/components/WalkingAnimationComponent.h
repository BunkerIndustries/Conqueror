#pragma once
#include "Engine.h"

class WalkingAnimation : public Component {
public:
	WalkingAnimation();
	WalkingAnimation(glm::vec2 indexStartUp, glm::vec2 IndexEndUp, glm::vec2 IndexStartDown, glm::vec2 indexEndDown, glm::vec2 indexStartRight, glm::vec2 IndexEndRight, glm::vec2 IndexStartLeft, glm::vec2 indexEndLeft, int animationSpeed, int spriteSheetLength);
	void OnStart() override { }
	void OnStop() override { }
	void OnUpdate() override;
	void OnEvent(Event& event) override {};
	std::string CalculateDirection();
	void Start(glm::vec2 indexStart, glm::vec2 indexEnd);


private:
	int max;
	int animationSpeed;
	int spriteSheetLength;
	glm::vec2 indexStart;
	glm::vec2 indexEnd;
	glm::vec2 indexStartUp;
	glm::vec2 indexEndUp;
	glm::vec2 indexStartDown;
	glm::vec2 indexEndDown;
	glm::vec2 indexStartLeft;
	glm::vec2 indexEndLeft;
	glm::vec2 indexStartRight;
	glm::vec2 indexEndRight;
};