#pragma once
#include "Engine.h"
#include "movement.h"

class EnemyBehaviour : public Component {
public:
	EnemyBehaviour();
	virtual ~EnemyBehaviour() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	size_t GetYIndex();

private:
	Movement* move_component = nullptr;
	bool is_waiting = false;
	bool time_over = false;
	bool time_running = false;

	float time_to_wait = 0.0f;
	float dt_time_counter = 0.0f;

	size_t x_index = 0;
	size_t y_index = 0;

	void ChoosePosAndMove();
};
