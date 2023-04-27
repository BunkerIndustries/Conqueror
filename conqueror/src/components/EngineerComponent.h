#pragma once
#include "_Game.h"
#include "required/stands.h"

class EngineerBuilding : public Component
{
public:
	EngineerBuilding(uint32_t engineerCount);
	~EngineerBuilding() override = default;

	void OnStart() override {};
	void OnStop() override {};
	void OnUpdate() override {};
	void OnEvent(Event& event) override {};

	void SendEngineer();
	void IncreaseAvailableEngineers();

	void IncreaseMgStock();
	void IncreaseArtilleryStock();

private:
	uint32_t available_engineers;
	uint32_t available_mgs;
	uint32_t available_artillery;
};

class EngineerCharacter : public Component {
public:
	EngineerCharacter(std::vector<GameObject*>& nodes);
	virtual ~EngineerCharacter() = default;

	void OnStart() override { };
	void OnStop() override { };
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	GameObject* engineer_building;
	GameObject* building_node;
	glm::vec2 building_node_position;
	std::vector<GameObject*> nodes;

	GameObject* ChooseBuildingNode();

	bool isBuilding;
	bool going_back;
	float dt_counter;
};

