#pragma once
#include "Engine.h"

class ArtilleryComponent : public Component {
public:
	ArtilleryComponent(GameObject* own_node);
	virtual ~ArtilleryComponent() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	float dt_counter;
	float reload_time;
	Node* own_node;
	Sound shoot;

	void Shoot();
};