#pragma once
#include "Engine.h"

class SoldierShooting : public Component {
public:
	SoldierShooting();
	virtual ~SoldierShooting() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	void Shoot();

	void NullTarget()
	{
		target = nullptr;
	}

private:
	bool LockTarget();

	GameObject* target;
	uint8_t hit_probability;
};
