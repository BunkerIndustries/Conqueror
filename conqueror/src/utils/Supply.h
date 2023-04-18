#pragma once

#include "required/constants.h"

class Supply {
public:
	static void Init();
	static void TryCallSoldier();

	static void TakeChoices();
	static void IncreaseSoldierCount();

private:
	static unsigned int soldier_stock;
	static uint8_t min_soldiers, max_soldiers;

	static uint8_t soldiers;
};