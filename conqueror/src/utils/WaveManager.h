#pragma once
#include "_Game.h"

class GameScene;

class WaveManager {
public:
	WaveManager(GameScene* gameScene);
	~WaveManager() = default;

	void OnUpdate();
	void CheckForEnemiesDead();

	int GetWaveCount();

	static void Init();

	static Shr<Sound> sound_wave;

private:
	GameScene* gameScene;

	bool cooldown_state;
	bool enemies_are_dead;
	bool just_started;
	float cooldown_duration;
	float wave_duration;

	float global_dt_counter;

	float spawn_dt_counter;
	float spawn_interval;

	int wave_counter = 0;
};