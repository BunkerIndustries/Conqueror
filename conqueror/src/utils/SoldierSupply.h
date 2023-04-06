#pragma once

#include "required/constants.h"

class SoldierSupply {
public:
	static void Init();
	static void TryCallSoldier();

private:
	static unsigned int soldier_stock;
};