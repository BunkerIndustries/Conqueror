#pragma once
#include "_Game.h"

class MedicBuilding : public Component {
public:
	MedicBuilding(uint32_t number_of_medics);
	virtual ~MedicBuilding() = default;

	void OnStart() override { };
	void OnStop() override { };
	void OnUpdate() override { };
	void OnEvent(Event& event) override {};

	void SendMedic();
	void ReturnMedic();

private:
	uint32_t available_medics;
};

class MedicCharacter : public Component {
public:
	MedicCharacter(GameObject* home_node);
	virtual ~MedicCharacter() = default;

	void OnStart() override { };
	void OnStop() override { };
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	GameObject* home_node;
	GameObject* healing_target;
	glm::vec2 healing_target_position;

	bool healing;
	bool going_back;
	float heal_time;
	float dt_counter;
};
