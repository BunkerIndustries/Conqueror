#pragma once
#include "Engine.h"

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
	float hp;
	bool just_hit = false;
	float dt_counter = 0.0f;
};