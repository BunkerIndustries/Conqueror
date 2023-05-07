#pragma once
#include "Engine.h"

class MgComponent : public Component {
public:
	MgComponent(GameObject* own_node);
	virtual ~MgComponent() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};



private:
	GameObject* target;
	uint8_t hit_probability;
	unsigned int ammo;
	float dt_counter;

	Node* own_node;

	void LockTarget();
};