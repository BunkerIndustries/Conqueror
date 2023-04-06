#include "_Game.h"
#include "EngineerComponent.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

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

EngineerCharacter::EngineerCharacter(GameObject* home_node, GameObject* building_node)
	: home_node(home_node), building_node(building_node)
{
	building_node_position = home_node->transform.position + engineer_building_position_offset;
	gameObject->GetComponent<Movement>()->target_position = &building_node_position;
	isBuilding = false;
	going_back = false;
	dt_counter = 0.0f;
}



void EngineerCharacter::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == home_node->transform.position) {
			home_node->GetComponent<EngineerBuilding>()->ReturnEngineer();
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
			gameObject->GetComponent<Movement>()->target_position = &home_node->transform.position;
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