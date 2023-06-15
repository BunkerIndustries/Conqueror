#include "_Game.h"
#include "Economy.h"

int Economy::Balance = 5000;

void Economy::AddBalance(int amount) {
	Balance += amount;
}

void Economy::RemoveBalance(int amount) {
	Balance -= amount;
}

int Economy::getBalance() {
	return Balance;
}