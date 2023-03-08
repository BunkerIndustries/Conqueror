#include "soldier_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/bullet.h"


SoldierShooting::SoldierShooting() {

}

void SoldierShooting::start() {
	target = nullptr;
}

void SoldierShooting::stop() {

}

void SoldierShooting::update(float dt) {

}

void SoldierShooting::Shoot() {

	if (!LockTarget()) return;
	LOG_DEBUG("Shoot");
	bullet = new GameObject("bullet", Transform(gameObject->transform.position, bullet_size));

	// if the hit has hit
	if (RandomInt(0, max_hit_probability) <= hit_probability) {
		bullet->AddComponent(new Bullet(target, true));
	}
	else {
		bullet->AddComponent(new Bullet(target, false));
	}

}

#define ld LOG_DEBUG
bool SoldierShooting::LockTarget() {

	// has the effect that a soldier remains on one target if it has chosen it before
	if (target != nullptr) return true;

	std::vector<GameObject*> enemy_row_vec;

	// used for choosing the enemy-row randomly
	int random = RandomInt(0, SumTo(enemy_grid_y));
	size_t prob = 0;

	// choose 1 random row of the enemy grid
	int y_row;
	for (uint8_t i = 1; i <= enemy_grid_y; i++) {
		prob += i;
		if (random <= prob) {
			y_row = i-1;
			hit_probability = i;
			break;
		}
	}

	// copy all enemies who are in the randomly chosen row into another vector
	for (size_t i = 0; i < enemy_grid_x; i++) {
		if (enemy_stands[y_row][i] != nullptr) enemy_row_vec.push_back(enemy_stands[y_row][i]);
	}

	// if this vector contains no enemies => no target is set, try unsuccessful
	if (enemy_row_vec.size() == 0) {
		LOG_DEBUG("chosen row contains no enemies");
		return false;
	}

	// if it contains enemies => a target is set, try successful
	else {
		target = enemy_row_vec.at(RandomInt(0, enemy_row_vec.size()-1));
		LOG_DEBUG("Target found");
		return true;
	}

}