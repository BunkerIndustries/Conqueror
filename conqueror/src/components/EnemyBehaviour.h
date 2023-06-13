#pragma once
#include "Engine.h"

class Movement;

class EnemyBehaviour : public Component {
public:
	EnemyBehaviour();
	virtual ~EnemyBehaviour() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override;

	GameObject* GetNode();

	size_t GetYIndex();
	size_t GetXIndex();
private:
	Movement* move_component = nullptr;
	bool is_waiting = false;
	bool time_over = false;
	bool time_running = false;
	bool onSpawnPos = true;

	float time_to_wait = 0.0f;
	float dt_time_counter = 0.0f;

	size_t x_index = 0;
	size_t y_index = 0;

	GameObject* node = nullptr;

	void ChoosePosAndMove();
	void TryLeaveSpawnPos();
};
