#include "_Game.h"

#include "Supply.h"
#include "required\functions.h"
#include "required/constants.h"

unsigned int Supply::soldier_stock;
uint8_t Supply::min_soldiers, max_soldiers;

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

std::string Supply::TakeChoices() {
	soldiers = RandomInt(min_soldiers, max_soldiers);

	std::string left_choices = { "medic", "engineer", "mg", "artillerie" };
	return choice = left_choices[RandomInt(0, 3)];
}

void Supply::IncreaseSoldierCount() {
	min_soldiers += soldier_increase_by_wave;
	max_soldiers += soldier_increase_by_wave;
}