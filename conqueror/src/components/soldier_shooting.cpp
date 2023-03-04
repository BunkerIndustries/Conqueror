#include "soldier_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/bullet.h"


SoldierShooting::SoldierShooting() {

}

void SoldierShooting::start() {

}

void SoldierShooting::stop() {

}

void SoldierShooting::update(float dt) {

}

void SoldierShooting::Shoot() {
	if (!LockTarget()) return;

	GameObject bullet = GameObject("bullet", Transform(gameObject->transform.position, bullet_size));

	// if the hit has hit
	if (RandomInt(0, max_hit_probability) <= *hit_probability) {
		bullet.AddComponent(new Bullet(target, true));
	}
	else {
		bullet.AddComponent(new Bullet(target, false));
	}

}

bool SoldierShooting::LockTarget() {

	std::vector<GameObject*> enemy_row_vec;

	int random = RandomInt(0, SumTo(enemy_grid_y));
	size_t prob = SumTo(enemy_grid_y);

	int y_row;
	// choose 1 random row of the enemy grid (probability increases from top to bottom)
	for (size_t i = enemy_grid_y - 1; i >= 0; i--) {
		prob -= i;
		if (random >= prob) {
			y_row = i;
			*hit_probability = i;
			break;
		}
	}

	// copy all enemies who are in the randomly chosen row into another vector
	for (size_t i = 0; i < enemy_grid_x; i++) {
		if (enemy_stands[y_row][i] != nullptr) enemy_row_vec.push_back(enemy_stands[y_row][i]);
	}

	// if this vector contains no enemies => no enemy get's locked
	if (enemy_row_vec.size() == 0) {
		return false;
	}

	// if it contains enemies
	else {
		target = enemy_row_vec.at(RandomInt(0, enemy_row_vec.size()-1));	// set a target
		return true;
	}

}