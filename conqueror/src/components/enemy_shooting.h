#pragma once
#include "Engine.h"

class EnemyShooting : public Component {
public:
	EnemyShooting();
	virtual ~EnemyShooting() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	void Shoot();

	void NullTarget()
	{
		target = nullptr;
	};
private:
	bool LockTarget();
	GameObject* target = nullptr;
	uint8_t hit_probability = 0;
};