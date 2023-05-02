#include "_Game.h"
#include "EnemyShooting.h"
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


		glm::vec2 end_point;

		int r = RandomInt(0, max_hit_probability);
		if (r <= hit_probability) {
			end_point = target->transform.position;
			if (target->GetComponent<Health>()->TakeDamage(enemy_damage)) target = nullptr;
		}
		else {
			end_point = glm::vec2(target->transform.position.x + RandomF(min_inaccuracy, max_inaccuracy) * RandomInt(-1, 1), target->transform.position.y);
		}
		
		GameObject* trace = new GameObject("bullet",Transform());
		trace->AddComponent(new LineRenderer(gameObject->transform.position, end_point, trace_color, trace_thickness, trace_lasting * game_time_factor));
		gameScene->enemyLayer->AddGameObjectToLayer(trace);


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