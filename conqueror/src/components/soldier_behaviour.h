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

	bool on_spawn_pos = true;
	bool is_healed = false;

private:
	float health = 0.0f;

	bool travelling  = false;

	bool SoldierTryMoveToWaitingNode();
	void RestartTimer();

	float dt_counter = 0.0f;
	float time_to_wait  = 0.0f;

	glm::vec2 target_position = glm::vec2(0.0f);

	std::vector<GameObject*>* stand = nullptr;
	GameObject* old_node = nullptr;
	Node* current_node = nullptr;
};