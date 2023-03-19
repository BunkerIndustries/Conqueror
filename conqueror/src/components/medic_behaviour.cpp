#include "medic_behaviour.h"
#include "components/movement.h"
#include "required/constants.h"

MedicBehaviour::MedicBehaviour(GameObject* healing_target)
	:healing_target(healing_target)
{

}

void MedicBehaviour::start() {
	gameObject->GetComponent<Movement>()->target_position = healing_target->transform.position + medic_healing_position_offset;
}

void MedicBehaviour::stop() {

}

void MedicBehaviour::update(float dt) {

	healing_target_position = healing_target->transform.position + medic_healing_position_offset;

	if (gameObject->transform.position != healing_target_position) return;
	

}