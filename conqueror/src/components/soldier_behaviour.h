#pragma once
#include "Engine.h"

class SoldierBehaviour : public Component {
public:
	SoldierBehaviour();
	virtual ~SoldierBehaviour() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	void SoldierMove(GameObject* node);
	void FreeNode();

	bool on_spawn_pos;
	bool is_healed;

private:
	float health;

	bool travelling;

	bool SoldierTryMoveToWaitingNode();
	void RestartTimer();

	float dt_counter;
	float time_to_wait;

	glm::vec2 target_position;

	std::vector<GameObject*>* stand = nullptr;
	GameObject* old_node = nullptr;
	Node* current_node = nullptr;
};