#pragma once
#include "Engine.h"
#include "generic/Sound.h"

class Health : public Component {
public:
	Health(float hp);
	virtual ~Health() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	bool TakeDamage(float damage);
	float GetHp();
	void GetHealed();
private:
	Sound death;
	Sound hit_soldier;
	Sound hit_enemy;

	float hp;
	bool just_hit = false;
	float dt_counter = 0.0f;
};