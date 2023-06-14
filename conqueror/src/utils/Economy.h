#pragma once
#include "_Game.h"

class Economy {
public:
	static void AddBalance(int amount);
	static void RemoveBalance(int amount);
	static int getBalance();
private:
	static int Balance;
};