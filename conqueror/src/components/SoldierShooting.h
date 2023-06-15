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

	static void Init();

	void Shoot();
	static std::shared_ptr<Sound> soldier_shoot;

private:
	GameObject* LockTarget();
	GameObject* GetTarget() const;
	uint8_t hit_probability;
};
