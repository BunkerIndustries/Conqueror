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
	Movement* move_component;
	bool is_waiting;
	bool time_over;
	bool time_running;

	float time_to_wait;
	float dt_time_counter;

	size_t x_index;
	size_t y_index;

	void ChoosePosAndMove();
};
