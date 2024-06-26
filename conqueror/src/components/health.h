#pragma once
#include "Engine.h"
#include "generic/Sound.h"

class Health : public Component {
public:
	Health(float hp);
	virtual ~Health() = default;

	static void Init();

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	bool TakeDamage(float damage);
	float GetHp();
	float GetMaxHp();
	void GetHealed();
	void AddMaxHp(float addHp);

	static Shr<Sound> death;
	static Shr<Sound> death_special;
	static Shr<Sound> hit_soldier;
	static Shr<Sound> hit_enemy;
private:


	float hp;
	bool just_hit = false;
	float dt_counter = 0.0f;
	float max_hp = soldier_health;
};