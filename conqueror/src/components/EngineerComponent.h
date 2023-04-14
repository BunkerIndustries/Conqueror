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
	void ReturnEngineer();

private:
	uint32_t available_engineers;
};

class EngineerCharacter : public Component {
public:
	EngineerCharacter(Stand& stand);
	virtual ~EngineerCharacter() = default;

	void OnStart() override { };
	void OnStop() override { };
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	GameObject* engineer_building;
	GameObject* building_node;
	glm::vec2 building_node_position;

	GameObject* ChooseBuildingNode(std::vector<GameObject*>* nodes);

	bool isBuilding;
	bool going_back;
	float dt_counter;
};

