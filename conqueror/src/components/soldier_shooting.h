#pragma once
#include "Engine.h"

class SoldierShooting : public Component {
public:
	SoldierShooting();
	virtual ~SoldierShooting() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void Shoot();

	void NullTarget()
	{
		target = nullptr;
	}

private:
	bool LockTarget();

	GameObject* bullet;
	GameObject* target;
	uint8_t hit_probability;
};
