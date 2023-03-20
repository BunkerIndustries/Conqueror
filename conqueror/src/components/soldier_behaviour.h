#pragma once
#include "Engine.h"

class SoldierBehaviour : public Component {
public:
	SoldierBehaviour();
	virtual ~SoldierBehaviour() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void SoldierMove(GameObject* node);

	bool on_spawn_pos;
	bool is_healed;

private:
	float health;

	bool can_shoot;
	bool travelling;

	bool SoldierTryMoveToWaitingNode();
	void RestartTimer();

	float dt_counter;
	float time_to_wait;

	glm::vec2 target_position;

	std::vector<GameObject*>* stand;
	GameObject* old_node;
};