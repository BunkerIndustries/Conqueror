#include "_Game.h"
#include "MedicComponent.h"

#include "required/constants.h"

MedicBuilding::MedicBuilding(uint32_t number_of_medics)
	:available_medics(number_of_medics)
{

}

void MedicBuilding::SendMedic() {
	
	if (available_medics <= 0) return;
	available_medics--;

	gameScene->allyLayer->CreateMedic(gameObject->transform.position);

}

void MedicBuilding::IncreaseAvailableMedics() {
	available_medics++;
}

MedicCharacter::MedicCharacter(GameObject* medic_building)
	:medic_building(medic_building)
{
	healing_target = gameScene->GetActiveCharacter();
	healing_target_position = gameScene->GetActiveCharacter()->transform.position + medic_healing_position_offset;
	healing = false;
	going_back = false;
	dt_counter = 0.0f;
	heal_time = 0.0f;
}

void MedicCharacter::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == medic_building->transform.position) {
			medic_building->GetComponent<MedicBuilding>()->IncreaseAvailableMedics();
			delete gameObject;
		}
		return;
	}

	// if the soldier is already dead
	if (!healing_target->GetComponent<Movement>()) {
		// go back 
		going_back = true;
		gameObject->GetComponent<Movement>()->SetTrackingPos(&medic_building->transform.position);
		return;
	}

	if ((gameObject->transform.position != healing_target_position) || going_back) return;	// if he has not arrived yet or is going back
	if (!healing) {	// if he arrived and is not healing already
		healing = true;
		heal_time = (soldier_health - healing_target->GetComponent<Health>()->GetHp()) * waiting_time_per_hp * game_time_factor;
	}
	else if (healing) {
		if (dt_counter >= heal_time) {
			healing = false;
			going_back = true;
			healing_target->GetComponent<Health>()->GetHealed();
			gameObject->GetComponent<Movement>()->target_position = &medic_building->transform.position;
		}
		dt_counter += Application::GetDT();
	}
}