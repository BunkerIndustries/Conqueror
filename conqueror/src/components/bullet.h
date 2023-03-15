#pragma once
#include "Engine.h"

class Bullet : public Component {
public:
	Bullet(GameObject* target, GameObject* parent, bool is_hit, float damage);
	virtual ~Bullet();

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

private:
	glm::vec2 target_position;
	GameObject* target;
	GameObject* parent;
	bool is_hit;
	float damage;
};
