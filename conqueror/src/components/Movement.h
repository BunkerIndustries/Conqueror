#pragma once
#include "Engine.h"

class Movement : public Component {
public:
	Movement(float movement_speed);
	Movement(float movement_speed, glm::vec2 pos);
	~Movement() override = default;

	void OnStart() override { }
	void OnStop() override { }
	void OnUpdate() override;
	void OnEvent(Event& event) override { }

	void SetTrackingPos(glm::vec2* pos);
	void SetTargetPos(glm::vec2 pos);

	glm::vec2* GetTrackingPos() const { return tracking_position; }
	glm::vec2 GetTargetPos() const { return target_position; }
	glm::vec2 GetDirection() const { return direction; }
	bool IsArrived() const { return isArrived; }

private:
	glm::vec2* tracking_position;
	glm::vec2 target_position;
	glm::vec2 direction;
	bool move;
	bool isArrived;
	float movement_speed;
	void MoveTo(glm::vec2 pos, float speed);
};