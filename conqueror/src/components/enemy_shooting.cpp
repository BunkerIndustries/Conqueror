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

bool EnemyShooting::LockTarget() {

	std::vector<GameObject*>* chosen_stand;

	int random = RandomInt(0, choose_probability_sum);
	LOG_DEBUG("random: {0}",random);

	uint8_t prob = 0;
	size_t i;
	for (i = 0; i < shootable_stands.size(); i++) {
		prob += *shootable_stands.at(i).choose_probability;
		LOG_DEBUG("prob: {0}", prob);
		if (random <= prob) {
			chosen_stand = shootable_stands.at(i).stand;
			LOG_DEBUG("chosen stand: {0}", i);
			break;
		}
		
	}

	if (chosen_stand->size() == 0) {
		return false;
	}
	else {
		target = chosen_stand->at(RandomInt(0, chosen_stand->size() - 1));
		hit_probability = shootable_stands.at(i).hit_probability;
		return true;
	}
	
}