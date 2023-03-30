#include "_Game.h"
#include "engineer_behaviour.h"
#include "components/movement.h"
#include "components/health.h"
#include "required/constants.h"
#include "required/functions.h"

EngineerBehaviour::EngineerBehaviour(GameObject* building_node)
	:building_node(building_node)
{

}

void EngineerBehaviour::OnStart() {
	building_node_position = building_node->transform.position + engineer_building_position_offset;
	gameObject->GetComponent<Movement>()->target_position = building_node_position;
	building = false;
	going_back = false;
	dt_counter = 0.0f;
}


void EngineerBehaviour::OnStop() {

}

void EngineerBehaviour::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == engineer_management->GetGameObject()->transform.position) {
			engineer_management->EngineerArrived();
			delete gameObject;
		}
		return;
	}

	if ((gameObject->transform.position != building_node_position) || going_back) return;	// if he has not arrived yet or is going back return
	else if (!building) {	// if he arrived and is not healing already
		building = true;
		CreateNode(building_node->transform.position, mg_stand);
		delete building_node;
		// TODO: place mg
	}
	else if (building) {
		if (dt_counter >= building_time) {
			building = false;
			going_back = true;
			gameObject->GetComponent<Movement>()->target_position = engineer_management->GetGameObject()->transform.position;
		}
		dt_counter += Application::GetDT();
	}
}