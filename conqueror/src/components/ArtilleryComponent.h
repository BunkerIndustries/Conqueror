#pragma once
#include "Engine.h"

class ArtilleryComponent : public Component {
public:
	ArtilleryComponent();
	virtual ~ArtilleryComponent() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	float dt_counter;
	float reload_time;
	void Shoot();
};