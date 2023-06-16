#pragma once
#include "Engine.h"

class SoldierBehaviour : public Component {
public:
	SoldierBehaviour();
	~SoldierBehaviour() override;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	void SoldierMove(GameObject* node);
	void FreeNode();

	void MedicSent();
	void MedicLeft();
	bool ReceivingMedic();

	int GetLevel();
	void AddLevel();
	int GetUpgradePrice();
	void SetUpgradePrice(int amount);

	std::string GetName();

	bool on_spawn_pos = true;
	std::string soldier_upgrade_price_display = std::to_string(soldier_upgrade_price_start);

private:
	float health = 0.0f;

	bool travelling = false;
	bool gets_healed = false;
	bool can_shoot = true;

	bool SoldierTryMoveToWaitingNode();
	void RestartTimer();

	float dt_counter = 0.0f;
	float time_to_wait  = 0.0f;

	int soldier_level = 1;
	int soldier_upgrade_price_int = 5;

	glm::vec2 target_position = glm::vec2(0.0f);

	std::vector<GameObject*>* stand = nullptr;
	GameObject* old_node = nullptr;
	Node* current_node = nullptr;

	std::string name;
};