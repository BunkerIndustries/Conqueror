#pragma once
#include "Engine.h"

class EnemyShooting : public Component {
public:
	EnemyShooting();
	virtual ~EnemyShooting() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void Shoot();
private:
	bool LockTarget();
	GameObject* target;
	uint8_t* hit_probability;
};