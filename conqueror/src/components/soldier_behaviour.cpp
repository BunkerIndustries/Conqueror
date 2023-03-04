#include "soldier_behaviour.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

#include "soldier_shooting.h"


SoldierBehaviour::SoldierBehaviour() {

}

void SoldierBehaviour::start() {
	can_shoot = false;
	time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time);
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

	gameObject->GetComponent<Movement>()->target_position = move_node->transform.position;
	travelling = true;

	std::vector<GameObject*>* old_stand = this->stand;

	// ERROR: node-component is nullptr
	Node* n = move_node->GetComponent<Node>();
	this->stand = move_node->GetComponent<Node>()->stand;

	for (size_t i = 0; i <= old_stand->size() - 1; i++) {
		if (old_stand->at(i) == gameObject) {
			old_stand->erase(old_stand->begin() + i);
			break;
		}
	}

}