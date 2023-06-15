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

	void DecreaseMgStock();
	void DecreaseArtilleryStock();

	void UpgradeBuilding();

	uint8_t GetMgStock();
	uint8_t GetArtilleryStock();

	uint8_t GetAvailableEngineers();
	int building_level;
	int building_upgrade_price;
	std::string building_upgrade_price_display;

private:
	uint32_t available_engineers;
	uint32_t available_mgs;
	uint32_t available_artillery;

};

class EngineerCharacter : public Component {
public:
	EngineerCharacter(bool mg_artillery);
	virtual ~EngineerCharacter() = default;

	void OnStart() override;
	void OnStop() override { };
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	std::string GetName();
private:
	GameObject* engineer_building;
	GameObject* building_node;
	glm::vec2 building_node_position;
	bool mg_artillery;

	GameObject* ChooseBuildingNode();

	bool isBuilding;
	bool going_back;
	float dt_counter;
	std::string name;
};

