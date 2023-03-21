#pragma once
#include "Engine.h"

class Bullet : public Component {
public:
	Bullet(GameObject* target, GameObject* parent, bool is_hit, float damage);
	virtual ~Bullet();

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	glm::vec2 target_position;
	GameObject* target;
	GameObject* parent;
	bool is_hit;
	float damage;
};
