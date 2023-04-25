#include "_Game.h"
#include "soldier_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"



SoldierShooting::SoldierShooting() {

}

void SoldierShooting::OnStart() {
	target = nullptr;
}

void SoldierShooting::OnStop() {
	
}

void SoldierShooting::OnUpdate() {

}

void SoldierShooting::Shoot() {
	
	for (uint8_t i = 0; i < max_soldier_lock_target_tries; i++) {
		if (!LockTarget()) continue;

		gameScene->CreateBullet(gameScene->allyLayer, target, gameObject->transform.position, target->transform.position);
		
		break;
	}

}

bool SoldierShooting::LockTarget() {
	// check if target already exists
	LOG_DEBUG(target->GetName());
	if (target) {
		return true;
	}

	// choose a random row of enemies
	std::vector<GameObject*> enemies_in_row;
	int row = RandomInt(0, SumTo(enemy_grid_y));
	int prob = 0;
	for (int i = 1; i <= enemy_grid_y; i++) {
		prob += i;
		if (row <= prob) {
			row = i - 1;
			hit_probability = i;
			break;
		}
	}
	for (int i = 0; i < enemy_grid_x; i++) {
		if (enemy_stands[row][i]) {
			enemies_in_row.push_back(enemy_stands[row][i]);
		}
	}

	// if no enemies in row, return false
	if (enemies_in_row.empty()) {
		return false;
	}

	// set random enemy in row as target and return true
	target = enemies_in_row[RandomInt(0, enemies_in_row.size() - 1)];
	Util::shootingTable[target].push_back(this);
	return true;
}