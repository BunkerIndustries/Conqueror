#pragma once
#include "Engine.h"

class Movement : public Component {
public:
	Movement();
	virtual ~Movement() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void MoveTo(glm::vec2 pos, float speed);

	glm::vec2 target_position;
	float movement_speed;

};