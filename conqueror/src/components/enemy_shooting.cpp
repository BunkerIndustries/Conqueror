#include "enemy_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/bullet.h"


EnemyShooting::EnemyShooting() {

}

void EnemyShooting::start() {

}

void EnemyShooting::stop() {

}

void EnemyShooting::update(float dt) {

}

void EnemyShooting::Shoot() {

	// he has max max_enemy_lock_target_tries tries, if no character is found => cancel shooting
	for (uint8_t i = 0; i < max_enemy_lock_target_tries; i++) {

		// if a target is found => instantiate bullet and calulate whether it will hit or not, stop target-searching-process
		if (!LockTarget()) continue;
		LOG_DEBUG("LockTarget() returned true");
		GameObject* bullet = new GameObject("bullet", Transform(gameObject->transform.position, bullet_size));

		bullet->AddComponent(new SpriteRenderer(bullet_color));

		int r = RandomInt(0, max_hit_probability);

		// if the hit is supposed to hit => create new bullet and let it hit the enemy
		if (r <= hit_probability) {
			//LOG_DEBUG("Shoot and hit");
			bullet->AddComponent(new Bullet(target, true, enemy_damage));
		}

		// if the hit is not supposed to hit => create new bullet and let it miss the enemy
		else {
			//LOG_DEBUG("Shoot and miss");
			bullet->AddComponent(new Bullet(target, false, enemy_damage));
		}

		foreground_layer->AddGameObjectToLayer(bullet);

		break;

	}
}


bool EnemyShooting::LockTarget() {

	std::vector<GameObject*>* chosen_stand;

	// used for choosing the enemy-row randomly
	int random = RandomInt(0, choose_probability_sum);
	uint8_t prob = 0;

	// choose 1 random row of the character stands
	size_t i;
	for (i = 0; i < shootable_stands.size(); i++) {
		prob += *shootable_stands.at(i).choose_probability;

		if (random <= prob) {
			chosen_stand = shootable_stands.at(i).stand;
			break;
		}

	}

	// if the randomly chosen stand contains no characters => try unsuccessful
	if (chosen_stand->size() == 0) {
		return false;
	}

	// if the randomly chosen stand contains characters => target is set, try successful
	else {
		//std::cout << "target found at " << &chosen_stand << std::endl;
		target = chosen_stand->at(RandomInt(0, chosen_stand->size() - 1));
		hit_probability = *shootable_stands.at(i).hit_probability;
		return true;
	}

}