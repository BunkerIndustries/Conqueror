#include "_Game.h"
#include "engineer_behaviour.h"
#include "components/movement.h"
#include "components/health.h"
#include "required/constants.h"

EngineerBehaviour::EngineerBehaviour(GameObject* building_node)
	:building_node(building_node)
{

}

void EngineerBehaviour::OnStart() {
	healing_target_position = building_node->transform.position + medic_healing_position_offset;
	gameObject->GetComponent<Movement>()->target_position = healing_target_position;
	healing = false;
	going_back = false;
	dt_counter = 0.0f;
}


void EngineerBehaviour::OnStop() {

}

void EngineerBehaviour::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == medic_management->GetGameObject()->transform.position) {
			medic_management->MedicArrived();
			delete gameObject;
		}
		return;
	}

	// if the soldier is already dead
	if (!healing_target->GetComponent<Movement>()) {
		// go back 
		going_back = true;
		gameObject->GetComponent<Movement>()->target_position = medic_management->GetGameObject()->transform.position;
		return;
	}

	if ((gameObject->transform.position != healing_target_position) || going_back) return;	// if he has not arrived yet or is going back
	else if (healing == false) {	// if he arrived and is not healing already
		healing = true;
		heal_time = (soldier_health - healing_target->GetComponent<Health>()->GetHp()) * waiting_time_per_hp * game_time_factor;
	}
	else if (healing == true) {
		if (dt_counter >= heal_time) {
			healing = false;
			going_back = true;
			healing_target->GetComponent<Health>()->GetHealed();
			gameObject->GetComponent<Movement>()->target_position = medic_management->GetGameObject()->transform.position;
		}
		dt_counter += Application::GetDT();
	}
}