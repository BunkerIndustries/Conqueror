#include "_Game.h"
#include "WaveManager.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"
#include "required/functions.h"
#include "utils/Supply.h"

Shr<Sound> WaveManager::sound_wave;

WaveManager::WaveManager(GameScene* gameScene)
	: gameScene(gameScene)
{
	global_dt_counter = 0.0f;
	spawn_dt_counter = 0.0f;
	cooldown_state = true;
	just_started = true;

	enemies_are_dead = true;

	cooldown_duration = start_preparation_time * game_time_factor;
	wave_duration = start_wave_duration * game_time_factor;
	spawn_interval = enemy_start_spawn_interval * game_time_factor;
}

void WaveManager::Init()
{
	sound_wave = MakeShr<Sound>();
	sound_wave->LoadSound("assets/sounds/next_wave.wav");
}

void WaveManager::OnUpdate() {

	float dt = Application::GetDT();
	global_dt_counter += dt;

	if (cooldown_state) {
		if (global_dt_counter >= cooldown_duration) {
			LOG_DEBUG("cooldown over - wave state");
			cooldown_duration += cooldown_addition * game_time_factor;
			cooldown_state = false;
			enemies_are_dead = false;
			global_dt_counter = 0.0f;
			if (just_started) {
				just_started = false;
				return;
			}
		}
		return;
	}

	if (global_dt_counter <= wave_duration) {
		if (spawn_dt_counter >= spawn_interval) {
			gameScene->enemyLayer->CreateEnemy("enemy", glm::vec2(RandomF(enemy_grid_startpos.x - enemy_spawn_random_x_radius, enemy_grid_startpos.x + enemy_spawn_random_x_radius), enemy_spawn_y_position));
			spawn_dt_counter = 0.0f;
		}
		else {
			spawn_dt_counter += dt;
		}
	}
	else {
		if (!enemies_are_dead) return;
		sound_wave->SoundPlay();
		LOG_DEBUG("Wave over - cooldown state");
		wave_counter++;
		Supply::IncreaseSoldierCount();
		cooldown_state = true;
		gameScene->uiLayer->ActivateSupplyMenuUI();
		global_dt_counter = 0.0f;
		wave_duration *= wave_length_gradient;
		spawn_interval *= enemy_spawn_interval_gradient;
		return;
	}
}

void WaveManager::CheckForEnemiesDead() {
	if (gameScene->enemyLayer->GetGameObjectsByTag("enemy").size() > 1) return;

	enemies_are_dead = true;
}

int WaveManager::GetWaveCount() { return wave_counter; }