#include "medic_management.h"
#include "required/constants.h"
#include "required/functions.h"
#include "components/medic_behaviour.h"

MedicManagement::MedicManagement(uint8_t number_of_medics)
	:available_medics(number_of_medics)
{

}

void MedicManagement::start() {
	
}

void MedicManagement::stop() {

}

void MedicManagement::update(float dt) {

}

void MedicManagement::SendMedic(GameObject* healing_target) {
	if (available_medics <= 0) return;
	
	available_medics--;

	GameObject* medic = CreateCharacter("medic", gameObject->transform.position);
	medic->AddComponent(new MedicBehaviour(healing_target));

}

void MedicManagement::MedicArrived() {
	available_medics++;
}