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

	GameObject* GetTarget() const
	{
		return target;
	}

	void NullTarget()
	{
		target = nullptr;
	}

	static std::unordered_map<GameObject*, GameObject*> trackTable;

private:
	bool LockTarget();

	void UnlockTarget(GameObject* target) const;

	GameObject* target;
	uint8_t hit_probability;
};
