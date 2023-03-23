#pragma once
#include "Engine.h"

class WaveManager : public Component {
public:
	WaveManager();
	virtual ~WaveManager() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	bool cooldown_state;
	float cooldown_duration;
	float wave_duration;

	float global_dt_counter;
	
	float spawn_dt_counter;
	float spawn_interval;
};