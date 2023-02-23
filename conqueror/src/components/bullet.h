#pragma once
#include "Engine.h"

class Bullet : public Component {
public:
	Bullet(GameObject* target, bool is_hit);
	virtual ~Bullet() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

private:
	glm::vec2 target_position;
	bool is_hit;
};
