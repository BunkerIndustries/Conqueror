#include "_Game.h"
#include "EngineerComponent.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "SingleAnimationComponent.h"
#include "required/names.h"

EngineerBuilding::EngineerBuilding(uint32_t engineerCount)
	: available_engineers(engineerCount) {
	available_mgs = 0;
	available_artillery = 0;
	building_level = 1;
}

void EngineerBuilding::UpgradeBuilding() {
	engineer_speed_upgrade += 0.15 + building_level/10;
	mg_damage_upgrade += 3;
	building_level++;
}
void EngineerBuilding::SendEngineer()
{
	available_engineers--;
	gameScene->uiLayer->DeactivateBuildingUI();
	gameScene->uiLayer->ActivateEngineerBuildingUI();
}

void EngineerBuilding::IncreaseAvailableEngineers()
{
	available_engineers++;
	gameScene->uiLayer->DeactivateBuildingUI();
	gameScene->uiLayer->ActivateEngineerBuildingUI();
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

uint8_t EngineerBuilding::GetAvailableEngineers() {
	return available_engineers;
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
	name = names.at(RandomInt(0, names.size() - 1));
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
			gameObject->GetComponent<SingleAnimation>()->StopAnimation();
			isBuilding = false;
			going_back = true;
			gameObject->GetComponent<Movement>()->SetTrackingPos(&engineer_building->transform.position);

			float rotation = building_node->transform.rotation;

			if (mg_artillery) {
				GameObject* mg_node = gameScene->mapLayer->CreateNode(building_node->transform.position, mg_stand);
				gameScene->mapLayer->CreateMg(building_node->transform.position + mg_position_offset, mg_node);
				mg_node->transform.rotation = rotation;

			}
			else {
				GameObject* artillery_node = gameScene->mapLayer->CreateNode(building_node->transform.position, artillerie_stand);
				gameScene->mapLayer->CreateArtillery(building_node->transform.position + artillery_position_offset, artillery_node);
				artillery_node->transform.rotation = rotation;
			}
			delete building_node;
		}
		else {
			gameObject->GetComponent<SingleAnimation>()->PlayAnimation(false);
		}
		dt_counter += Application::GetDT();
		return;
	}
	// if he arrived and is not building already
	isBuilding = true;
	dt_counter = 0.0f;
}