#pragma once
#include "_Game.h"

class GameScene;

class WaveManager {
public:
	WaveManager(GameScene* gameScene);
	~WaveManager() = default;

	void OnUpdate();

private:
	GameScene* gameScene;

	bool cooldown_state;
	bool just_started;
	float cooldown_duration;
	float wave_duration;

	float global_dt_counter;

	float spawn_dt_counter;
	float spawn_interval;
};