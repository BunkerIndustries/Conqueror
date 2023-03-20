#include "soldier_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/bullet.h"


SoldierShooting::SoldierShooting() {

}

void SoldierShooting::start() {
	target = nullptr;
	bullet = nullptr;
}

void SoldierShooting::stop() {
	
}

void SoldierShooting::update(float dt) {

}

void SoldierShooting::Shoot() {
	
	for (uint8_t i = 0; i < max_soldier_lock_target_tries; i++) {
		if (!LockTarget()) continue;
		//LOG_DEBUG("LockTarget() returned true at try {0}", i);
		std::cout << "target: " << target << std::endl;

		bullet = new GameObject("bullet", Transform(gameObject->transform.position, bullet_size));

		bullet->AddComponent(new SpriteRenderer(bullet_color));


		// if the hit has hit
		if (RandomInt(0, enemy_grid_y + soldier_miss_points) <= hit_probability) {
			//LOG_DEBUG("soldier Bullet sent with hit=true");
			bullet->AddComponent(new Bullet(target, this->gameObject, true, soldier_damage));
		}
		else {
			//LOG_DEBUG("soldier Bullet sent with hit=false");
			bullet->AddComponent(new Bullet(target, this->gameObject, false, soldier_damage));
		}

		foreground_layer->AddGameObjectToLayer(bullet);

		break;
	}
	
}

bool SoldierShooting::LockTarget() {

	// the soldier will stay on the preselected target if it's still existing
	if (target != nullptr) return true;

	std::vector<GameObject*> enemy_row_vec;

	// used for choosing the enemy-row randomly
	int random = RandomInt(0, SumTo(enemy_grid_y));
	size_t prob = 0;

	// choose 1 random row of the enemy grid
	int y_row = 0;
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

		return false;
		// if no new target is found, remain on the old one
		//if (target != nullptr) {
		//	return true;
		//}
		//else {
		//	return false;
		//}
		
	}
	// if it contains enemies => a target is set, try successful
	else {
		target = enemy_row_vec.at(RandomInt(0, enemy_row_vec.size()-1));
		//LOG_DEBUG("Target found");
		return true;
	}

}