#include "_Game.h"
#include "EngineerComponent.h"

#include "required/constants.h"
#include "required/functions.h"

EngineerBuilding::EngineerBuilding(uint32_t engineerCount)
	: available_engineers(engineerCount) {
	available_mgs = 1;
	available_artillery = 1;
}

void EngineerBuilding::SendEngineer()
{
	available_engineers--;
}

void EngineerBuilding::IncreaseAvailableEngineers()
{
	available_engineers++;
}

void EngineerBuilding::IncreaseMgStock()
{
	available_mgs++;
}
void EngineerBuilding::IncreaseArtilleryStock()
{
	available_artillery++;
}

EngineerCharacter::EngineerCharacter(std::vector<GameObject*>& nodes)
{
	engineer_building = gameScene->mapLayer->engineerBuilding;
	building_node = ChooseBuildingNode();
	building_node_position = building_node->transform.position + engineer_building_position_offset;
	gameObject->GetComponent<Movement>()->SetTrackingPos(&building_node_position);
	nodes = nodes;
	isBuilding = false;
	going_back = false;
	dt_counter = 0.0f;
}

GameObject* EngineerCharacter::ChooseBuildingNode() {
	std::vector<GameObject*> valid_nodes;
	for (auto node : nodes) {
		if (!node->GetComponent<Node>()->is_occupied) valid_nodes.push_back(node);
	}
		
	return valid_nodes.at(RandomInt(0, valid_nodes.size() - 1));
}

void EngineerCharacter::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == engineer_building->transform.position) {
			engineer_building->GetComponent<EngineerBuilding>()->IncreaseAvailableEngineers();
			delete gameObject;
		}
		return;
	}

	if (gameObject->transform.position != building_node_position || going_back) return;	// if he has not arrived yet or is going back return
	if (isBuilding)
	{
		if (dt_counter >= building_time) {
			isBuilding = false;
			going_back = true;
			gameObject->GetComponent<Movement>()->SetTrackingPos(&engineer_building->transform.position);
		}
		dt_counter += Application::GetDT();
		return;
	}
	// if he arrived and is not building already
	isBuilding = true;
	gameScene->mapLayer->CreateNode(building_node->transform.position, mg_stand);
	delete building_node;

	if (building_node->GetComponent<Node>()->stand == trench_stand.stand) {
		gameScene->allyLayer->CreateMg(building_node_position);
	}
	else if (building_node->GetComponent<Node>()->stand == waiting_stand.stand) {
		gameScene->allyLayer->CreateArtillery(building_node_position);
	}
}