#pragma once
#include "Engine.h"

class EnemyShooting : public Component {
public:
	EnemyShooting();
	virtual ~EnemyShooting() = default;

	static void Init();
	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	void Shoot();

	static std::shared_ptr<Sound> enemy_shoot;

	GameObject* GetTarget() const;
private:
	GameObject* LockTarget();
	uint8_t hit_probability = 0;
};