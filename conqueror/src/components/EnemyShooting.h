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

private:
	GameObject* LockTarget();
	GameObject* GetTarget() const;
	uint8_t hit_probability = 0;
};