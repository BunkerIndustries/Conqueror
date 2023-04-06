#include "_Game.h"

#include "SoldierSupply.h"
unsigned int SoldierSupply::soldier_stock;

void SoldierSupply::Init() {
	soldier_stock = start_soldier_stock;
}

void SoldierSupply::TryCallSoldier() {
	if (soldier_stock <= 0) return;

	gameScene->allyLayer->CreateCharacter("soldier", Transform(soldier_spawn_pos, character_scale));
	soldier_stock--;
}