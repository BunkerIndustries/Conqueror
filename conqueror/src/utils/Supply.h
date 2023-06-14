#pragma once

#include "required/constants.h"

class Supply {
public:
	static void Init();
	static void TryCallSoldier();
	static void IncreaseSoldierCount();

	static uint8_t CreateLeftOption();
	static std::string CreateRightOption();
	static void TakeLeftOption();
	static void TakeRightOption();

	static bool CheckForGameOver();

	static int GetSoldiers();
	static void IncreaseSoldiers();
	static void DecreaseSoldiers();

private:
	static unsigned int soldier_stock;
	static uint8_t min_soldiers, max_soldiers;

	static int soldiers;

	static uint8_t left_option;
	static std::string right_option;
};
