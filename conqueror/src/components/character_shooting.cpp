#include "character_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/bullet.h"


CharacterShooting::CharacterShooting() {

}

void CharacterShooting::start() {

}

void CharacterShooting::stop() {

}

void CharacterShooting::update(float dt) {

}

void CharacterShooting::Shoot() {

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

bool CharacterShooting::LockTarget() {

	std::vector<GameObject*>* enemy_row;

	int random = RandomInt(0, SumTo(enemy_grid_y));
	size_t prob = SumTo(enemy_grid_y);

	// choose 1 random row of the enemy grid (probability raises from top to bottom)
	for (size_t i = enemy_grid_y - 1; i >= 0; i--) {
		prob -= i;
		if (random >= prob) {
			enemy_row = &enemy_stands.at(i);
			*hit_probability = i;
			break;
		}
	}

	// if this row contains no enemies
	if (enemy_row->size() == 0) {
		return false;
	}

	// if it contains enemies
	else {
		target = enemy_row->at(RandomInt(0, enemy_row->size() - 1));
		return true;
	}

}