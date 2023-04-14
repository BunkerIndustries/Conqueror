#include "_Game.h"
#include "EngineerComponent.h"

#include "required/constants.h"
#include "required/functions.h"

EngineerBuilding::EngineerBuilding(uint32_t engineerCount)
	: available_engineers(engineerCount) { }

void EngineerBuilding::SendEngineer()
{
	available_engineers--;
}

void EngineerBuilding::ReturnEngineer()
{
	available_engineers++;
}


EngineerCharacter::EngineerCharacter(Stand& stand) 
{
	engineer_building = gameScene->mapLayer->engineerBuilding;
	building_node = ChooseBuildingNode(stand.stand);
	building_node_position = building_node->transform.position + engineer_building_position_offset;
	gameObject->GetComponent<Movement>()->target_position = &building_node_position;

	isBuilding = false;
	going_back = false;
	dt_counter = 0.0f;
}

GameObject* EngineerCharacter::ChooseBuildingNode(std::vector<GameObject*>* nodes) {
	std::vector<GameObject*> valid_nodes;
	for (auto node : *nodes) {
		if (!node->GetComponent<Node>()->is_occupied) valid_nodes.push_back(node);
	}
		
	return valid_nodes.at(RandomInt(0, valid_nodes.size() - 1));
}

void EngineerCharacter::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == engineer_building->transform.position) {
			engineer_building->GetComponent<EngineerBuilding>()->ReturnEngineer();
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
			gameObject->GetComponent<Movement>()->target_position = &engineer_building->transform.position;
		}
		dt_counter += Application::GetDT();
		return;
	}
	// if he arrived and is not building already
	isBuilding = true;
	gameScene->mapLayer->CreateNode(building_node->transform.position, mg_stand);
	delete building_node;
	// TODO: place mg
}