#include "medic_behaviour.h"
#include "components/movement.h"
#include "components/health.h"
#include "required/constants.h"

MedicBehaviour::MedicBehaviour(GameObject* healing_target)
	:healing_target(healing_target)
{

}

void MedicBehaviour::start() {
	healing_target_position = healing_target->transform.position + medic_healing_position_offset;
	gameObject->GetComponent<Movement>()->target_position = healing_target_position;
	healing = false;
	going_back = false;
	LOG_DEBUG("healing_target_position: x:{0}", healing_target_position.x);
}


void MedicBehaviour::stop() {

}

void MedicBehaviour::update(float dt) {

	if (going_back) {
		if (gameObject->transform.position == medic_management->GetGameObject()->transform.position) gameObject->Delete();
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
		heal_time = (soldier_health - healing_target->GetComponent<Health>()->GetHp()) * waiting_time_per_hp * waiting_time_factor;
	}
	else if (healing == true) {

	}

}