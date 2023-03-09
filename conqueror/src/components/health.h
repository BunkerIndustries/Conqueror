#pragma once
#include "Engine.h"

class Health : public Component {
public:
	Health();
	virtual ~Health() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void TakeDamage(float damage);

private:
	float hp;
	void Die();
};