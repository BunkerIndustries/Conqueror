#include "_Game.h"

#include "Supply.h"
#include "required\functions.h"
#include "required/constants.h"

unsigned int Supply::soldier_stock;
int Supply::soldiers;
uint8_t Supply::min_soldiers;
uint8_t Supply::max_soldiers;
uint8_t Supply::left_option;
std::string Supply::right_option;
int Supply::soldierPrice;

Shr<Sound> Supply::click_supply;

void Supply::Init() {
	soldier_stock = start_soldier_stock;
	min_soldiers = 1;
	max_soldiers = start_max_soldiers;
	soldiers = 0;
	soldierPrice = soldier_start_price;

	click_supply = MakeShr<Sound>();

	click_supply->LoadSound("assets/sounds/click.wav");
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
	std::string right_choices[] = { "MG", "ARZT", "MECHANIKER", "MG", "ARZT", "ARTILLERIE" };
	std::string banana = right_choices[RandomInt(0, 5)];
	right_option = banana;
	return banana;
}

void Supply::TakeLeftOption() {
	soldier_stock += left_option;
	gameScene->uiLayer->DeactivateSupplyMenuUI();
	click_supply->SoundPlay();
}

void Supply::TakeRightOption() {
	if (right_option == "ARZT") {
		gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->IncreaseAvailableMedics();
	}
	else if (right_option == "MECHANIKER") {
		gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->IncreaseAvailableEngineers();
	}
	else if (right_option == "MG") {
		gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->IncreaseMgStock();
	}
	else if (right_option == "ARTILLERIE") {
		gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->IncreaseArtilleryStock();
	}
	gameScene->uiLayer->DeactivateSupplyMenuUI();
	
	click_supply->SoundPlay();
}

void Supply::IncreaseSoldierCount() {
	int wave_count = gameScene->waveManager->GetWaveCount();
	min_soldiers = std::round(wave_count / 2.4f);
	max_soldiers = std::round(wave_count / 2.0f);
	min_soldiers == 0 ? min_soldiers = 1 : false;
	max_soldiers == 0 ? max_soldiers = 1 : false;
}

void Supply::IncreaseSoldiers(){
	soldiers++;
}

void Supply::IncreaseSoldierStock(){
	soldier_stock++;
}

void Supply::DecreaseSoldiers() {
	soldiers--;
	LOG_DEBUG(soldiers);
}

int Supply::GetSoldiers() { return soldiers; }
int Supply::GetSoldierPrice() { return soldierPrice; }
void Supply::SetSoldierPrice(int amount) { soldierPrice = amount; }

bool Supply::CheckForGameOver() {

	// if soldiers still exist
	if (soldier_stock > 0 || gameScene->allyLayer->GetGameObjectsByTag("soldier").size() > 1){
		return false;
	}
	LOG_DEBUG("Scene change");
	waves_survived = gameScene->waveManager->GetWaveCount();
	Application::ChangeScene(gameOverScene);	// TODO: change to game-over menu
	return true;
}