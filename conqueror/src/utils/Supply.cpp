#include "_Game.h"

#include "Supply.h"
unsigned int Supply::soldier_stock;

void Supply::Init() {
	soldier_stock = start_soldier_stock;
}

void Supply::TryCallSoldier() {
	if (soldier_stock <= 0) return;

	gameScene->allyLayer->CreateSoldier(soldier_spawn_pos);
	soldier_stock--;
}