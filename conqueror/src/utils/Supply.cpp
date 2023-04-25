#include "_Game.h"

#include "Supply.h"
#include "required\functions.h"
#include "required/constants.h"

unsigned int Supply::soldier_stock;
uint8_t Supply::min_soldiers;
uint8_t Supply::max_soldiers;
uint8_t Supply::left_option;
std::string Supply::right_option;

void Supply::Init() {
	soldier_stock = start_soldier_stock;
	min_soldiers = min_soldiers_choice;
	max_soldiers = max_soldiers_choice;
	
}

void Supply::TryCallSoldier() {
	if (soldier_stock <= 0) return;

	gameScene->allyLayer->CreateSoldier(soldier_spawn_pos);
	soldier_stock--;
}

uint8_t Supply::CreateLeftOption() {
	uint8_t banana = RandomInt(min_soldiers, max_soldiers);
	left_option = banana;
	return banana;
}

std::string Supply::CreateRightOption() {
	std::string right_choices[4] = { "Medic", "Engineer", "Mg", "Artillerie" };
	std::string banana = right_choices[RandomInt(0, 3)];
	right_option = banana;
	return banana;
}

void Supply::TakeLeftOption() {
	soldier_stock += left_option;
	gameScene->uiLayer->DeactivateSupplyMenuUI();
}

void Supply::TakeRightOption() {
	if (right_option == "Medic") {
		gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->IncreaseAvailableMedics();
	}
	else if (right_option == "Engineer") {
		gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->IncreaseAvailableEngineers();
	}
	else if (right_option == "Mg") {
		gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->IncreaseMgStock();
	}
	else if (right_option == "Artillerie") {
		gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->IncreaseArtilleryStock();
	}
	gameScene->uiLayer->DeactivateSupplyMenuUI();
}

void Supply::IncreaseSoldierCount() {
	min_soldiers += soldier_increase_by_wave;
	max_soldiers += soldier_increase_by_wave;
}

bool Supply::CheckForGameOver() {

	// if soldiers still exist
	if (soldier_stock > 0 || gameScene->allyLayer->GetGameObjectsByTag("soldier").size() > 1) {
		return false;
	}
	LOG_DEBUG("Scene change");
	Application::ChangeScene(new MenuScene());	// TODO: change to game-over menu
	return true;
}