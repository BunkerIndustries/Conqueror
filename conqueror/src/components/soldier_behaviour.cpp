#include "soldier_behaviour.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

#include "soldier_shooting.h"


SoldierBehaviour::SoldierBehaviour() {

}

void SoldierBehaviour::start() {
	can_shoot = false;
	time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time) * waiting_time_factor;
	stand = waiting_stand.stand;
}

void SoldierBehaviour::stop() {

}

void SoldierBehaviour::update(float dt) {
	
	// if he's not walking
	if (!travelling) {
		if (this->stand != waiting_stand.stand) {
			if (!(dt_counter >= time_to_wait)) {
				dt_counter += dt;
			}
			else {
				gameObject->GetComponent<SoldierShooting>()->Shoot();
				dt_counter = 0.0f;
				time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time);
			}
		}
	}
	else {
		if (gameObject->GetComponent<Movement>()->has_arrived) {
			travelling = false;
			this->stand->push_back(gameObject);
		}
	}
}

void SoldierBehaviour::SoldierMove(GameObject* move_node) {

	Movement* move_component = gameObject->GetComponent<Movement>();

	if (move_component->target_position == move_node->transform.position) return;

	move_component->target_position = move_node->transform.position;
	travelling = true;

	for (size_t i = 0; i < stand->size(); i++) {
		if (stand->at(i) == gameObject) {
			stand->erase(stand->begin() + i);
			break;
		}
	}

	this->stand = move_node->GetComponent<Node>()->stand;
	
}