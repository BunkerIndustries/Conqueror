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

private:
	bool LockTarget();

	GameObject* bullet = nullptr;
	GameObject* target;
	uint8_t hit_probability;
};
