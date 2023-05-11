#include "_Game.h"
#include "EngineerComponent.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

EngineerBuilding::EngineerBuilding(uint32_t engineerCount)
	: available_engineers(engineerCount) {
	available_mgs = 0;
	available_artillery = 0;
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

void EngineerBuilding::DecreaseMgStock() {
	available_mgs--;
}

void EngineerBuilding::DecreaseArtilleryStock() {
	available_artillery--;
}

uint8_t EngineerBuilding::GetMgStock() {
	return available_mgs;
}

uint8_t EngineerBuilding::GetArtilleryStock() {
	return available_artillery;
}

EngineerCharacter::EngineerCharacter(bool mg_artillery)
{
	engineer_building = gameScene->mapLayer->engineerBuilding;
	this->mg_artillery = mg_artillery;
	building_node = ChooseBuildingNode();
	building_node->GetComponent<Node>()->is_occupied = true;
	building_node_position = building_node->transform.position + engineer_building_position_offset;
	isBuilding = false;
	going_back = false;
	dt_counter = 0.0f;
}

void EngineerCharacter::OnStart() {
	gameObject->GetComponent<Movement>()->SetTargetPos(building_node_position);
}

GameObject* EngineerCharacter::ChooseBuildingNode() {
	std::vector<GameObject*> nodes = mg_artillery ? trench_nodes : hiding_nodes;
	std::vector<GameObject*> valid_nodes;
	for (auto& node : nodes) {
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

			if (mg_artillery) {
				GameObject* mg_node = gameScene->mapLayer->CreateNode(building_node->transform.position, mg_stand);
				gameScene->allyLayer->CreateMg(building_node->transform.position + mg_position_offset, mg_node);
				gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->DecreaseMgStock();

			}
			else {
				GameObject* artillery_node = gameScene->mapLayer->CreateNode(building_node->transform.position, artillerie_stand);
				gameScene->allyLayer->CreateArtillery(building_node->transform.position + artillery_position_offset, artillery_node);
				gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->DecreaseArtilleryStock();
			}
			delete building_node;
		}
		dt_counter += Application::GetDT();
		return;
	}
	// if he arrived and is not building already
	isBuilding = true;
	dt_counter = 0.0f;
}