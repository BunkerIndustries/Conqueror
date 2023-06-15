#include "_Game.h"
#include "MedicComponent.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/names.h"

MedicBuilding::MedicBuilding(uint32_t number_of_medics)
	:available_medics(number_of_medics)
{
	building_level = 1;
	building_upgrade_price = medic_building_upgrade_price_start;
	building_upgrade_price_display = std::to_string(medic_building_upgrade_price_start);
}

void MedicBuilding::UpgradeBuilding() {
	medic_speed_upgrade += 0.3 + building_level / 10;
	building_level++;
	if (building_level % 2 == 0) {
		available_medics++;
	}
}

void MedicBuilding::SendMedic() {
	
	if (available_medics <= 0) return;
	available_medics--;

	gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->MedicSent();
	gameScene->allyLayer->CreateMedic(gameObject->transform.position);

	if (gameScene->GetActiveBuilding() == gameScene->mapLayer->medicBuilding) {
		gameScene->uiLayer->DeactivateBuildingUI();
		gameScene->uiLayer->ActivateMedicBuildingUI();
	}
}

void MedicBuilding::IncreaseAvailableMedics() {
	available_medics++;
	if (gameScene->GetActiveBuilding() == gameScene->mapLayer->medicBuilding) {
		gameScene->uiLayer->DeactivateBuildingUI();
		gameScene->uiLayer->ActivateMedicBuildingUI();
	}
}

uint32_t MedicBuilding::GetAvailableMedics() {
	return available_medics;
}

MedicCharacter::MedicCharacter(GameObject* medic_building)
	:medic_building(medic_building)
{
	healing_target = gameScene->GetActiveCharacter();
	healing_target_position = healing_target->transform.position + medic_healing_position_offset;
	healing = false;
	going_back = false;
	dt_counter = 0.0f;
	heal_time = 0.0f;
}

void MedicCharacter::OnStart() {
	gameObject->GetComponent<Movement>()->SetTargetPos(healing_target_position);
	name = names.at(RandomInt(0, names.size() - 1));
}

void MedicCharacter::OnUpdate() {

	if (going_back) {
		if (gameObject->transform.position == medic_building->transform.position) {
			medic_building->GetComponent<MedicBuilding>()->IncreaseAvailableMedics();
			LOG_DEBUG("medic reached medic-building");
			delete gameObject;
		}
		return;
	}

	// if the soldier is already dead
	if (!healing_target->GetComponent<SoldierBehaviour>()) {
		// go back 
		LOG_DEBUG("soldier to heal just died");
		going_back = true;
		gameObject->GetComponent<Movement>()->SetTrackingPos(&medic_building->transform.position);
		return;
	}

	if ((gameObject->transform.position != healing_target_position) || going_back) return;	// if he has not arrived yet or is going back
	if (!healing) {	// if he arrived and is not healing already
		LOG_DEBUG("medic just arrived at soldier to heal");
		healing_target->GetComponent<SpriteSheet>()->ChangeColor(heal_color);
		healing = true;
		heal_time = (healing_target->GetComponent<Health>()->GetMaxHp() - healing_target->GetComponent<Health>()->GetHp()) * waiting_time_per_hp * game_time_factor;
	}
	else if (healing) {
		if (dt_counter >= heal_time) {
			// healing is over
			LOG_DEBUG("medic just finished healing");
			healing_target->GetComponent<SpriteSheet>()->ChangeColor(white_color);
			healing = false;
			going_back = true;
			healing_target->GetComponent<Health>()->GetHealed();
			gameObject->GetComponent<Movement>()->SetTrackingPos(&medic_building->transform.position);
			healing_target->GetComponent<SoldierBehaviour>()->MedicLeft();
			if (gameScene->GetActiveCharacter() == healing_target) {
				gameScene->uiLayer->DeactivateCharacterUI();
				gameScene->uiLayer->ActivateSoldierUI();
			}
		}
		dt_counter += Application::GetDT();
	}
}

std::string MedicCharacter::GetName() { return name; }