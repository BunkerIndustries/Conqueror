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

	

	//TODO: foreground_layer->AddGameObjectToLayer(medic);

}

void MedicBuilding::ReturnMedic() {
	available_medics++;
}

MedicCharacter::MedicCharacter(GameObject* home_node, GameObject* healing_target)
	:home_node(home_node), healing_target(healing_target)
{
	healing_target_position = healing_target->transform.position + medic_healing_position_offset;
	healing = false;
	going_back = false;
	dt_counter = 0.0f;
	heal_time = 0.0f;
}

void MedicCharacter::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == home_node->transform.position) {
			home_node->GetComponent<MedicBuilding>()->ReturnMedic();
			delete gameObject;
		}
		return;
	}

	// if the soldier is already dead
	if (!healing_target->GetComponent<Movement>()) {
		// go back 
		going_back = true;
		gameObject->GetComponent<Movement>()->target_position = &home_node->transform.position;
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
			gameObject->GetComponent<Movement>()->target_position = &home_node->transform.position;
		}
		dt_counter += Application::GetDT();
	}
}