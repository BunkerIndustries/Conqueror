#include "_Game.h"
#include "enemy_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"


EnemyShooting::EnemyShooting() {

}

void EnemyShooting::OnStart() {

}

void EnemyShooting::OnStop() {

}

void EnemyShooting::OnUpdate() {

}

void EnemyShooting::Shoot() {

	// he has max max_enemy_lock_target_tries tries, if no character is found => cancel shooting
	for (uint8_t i = 0; i < max_enemy_lock_target_tries; i++) {

		// if a target is found => instantiate bullet and calulate whether it will hit or not, stop target-searching-process
		if (!LockTarget()) continue;
		//LOG_DEBUG("LockTarget() returned true");


		glm::vec2 distanceVec2 = target->transform.position - gameObject->transform.position;
		float dist = sqrt(distanceVec2.x * distanceVec2.x + distanceVec2.y * distanceVec2.y);

		glm::vec2 pos = target->transform.position;
		float distScale = dist / bulletInaccuracyMultiplicator;

		if (RandomInt(-dist, 2) < 0 && bulletDistanceMoreInaccuracy)
		{
			float randomX = RandomF(-1.0f, 1.0f) * distScale;
			pos.x += randomX;
		}


		gameScene->CreateBullet(gameScene->enemyLayer, target, gameObject->transform.position, pos);

		break;

	}
}


bool EnemyShooting::LockTarget() {

	//std::vector<GameObject*>* chosen_stand;
	//
	//// used for choosing the enemy-row randomly
	//int random = RandomInt(0, choose_probability_sum);
	//uint32_t prob = 0;
	//
	//// choose 1 random row of the character stands
	//size_t i;
	//for (i = 0; i < shootable_stands.size(); i++) {
	//	prob += *shootable_stands.at(i).choose_probability;
	//
	//	if (random <= prob) {
	//		chosen_stand = shootable_stands.at(i).stand;
	//		break;
	//	}
	//
	//}
	//
	//// if the randomly chosen stand contains no characters => try unsuccessful
	//if (chosen_stand->size() == 0) {
	//	return false;
	//}
	//
	//// if the randomly chosen stand contains characters => target is set, try successful
	//else {
	//	//std::cout << "target found at " << &chosen_stand << std::endl;
	//	target = chosen_stand->at(RandomInt(0, chosen_stand->size() - 1));
	//	hit_probability = *shootable_stands.at(i).hit_probability;
	//	return true;
	//}

	const std::vector<GameObject*>* chosen_stand = nullptr;

	// W‰hle eine zuf‰llige Reihe aus den schieﬂbaren St‰nden
	int random = RandomInt(0, choose_probability_sum);
	uint32_t prob = 0;

	size_t i = 0;
	for (; i < shootable_stands.size(); i++) {
		prob += *shootable_stands[i].choose_probability;
		if (random <= prob) {
			chosen_stand = shootable_stands[i].stand;
			break;
		}
	}

	// ‹berpr¸fe, ob die gew‰hlte Reihe Charaktere enth‰lt
	if (chosen_stand && chosen_stand->empty()) {
		return false;
	}
	
	// W‰hle zuf‰llig einen Charakter in der gew‰hlten Reihe als Ziel
	target = chosen_stand->at(RandomInt(0, chosen_stand->size() - 1));
	hit_probability = *shootable_stands[i].hit_probability;
	return true;

}