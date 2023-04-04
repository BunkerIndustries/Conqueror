#pragma once
#include "Engine.h"

class Movement : public Component {
public:
	Movement(float movement_speed);
	virtual ~Movement() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	glm::vec2* target_position;
	
	bool has_arrived;

private:
	float movement_speed;
	void MoveTo(glm::vec2 pos, float speed);
};