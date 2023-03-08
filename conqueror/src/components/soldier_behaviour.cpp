#include "soldier_behaviour.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

#include "soldier_shooting.h"


SoldierBehaviour::SoldierBehaviour(GameObject* start_node) 
	:old_node(start_node)
{

}

void SoldierBehaviour::start() {

	// start configuration
	can_shoot = false;
	time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time) * waiting_time_factor;
	stand = waiting_stand.stand;

	SoldierMove(old_node);
}

void SoldierBehaviour::stop() {

}

void SoldierBehaviour::update(float dt) {
	
	// if he's not walking
	if (!travelling) {

		// if he is not on the waiting stand
		if (this->stand != waiting_stand.stand) {

			// if time is not over => increase dt-time-counter by dt
			if (!(dt_counter >= time_to_wait)) {
				dt_counter += dt;
			}

			// if time is over => gameobject shoots and the waiting time get's calculated again
			else {
				gameObject->GetComponent<SoldierShooting>()->Shoot();
				dt_counter = 0.0f;
				time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time);
			}
		}
	}

	// if he arrived at the new node => the stand the node it's in get's extended by the gameobject
	else {
		if (gameObject->GetComponent<Movement>()->has_arrived) {
			travelling = false;
			this->stand->push_back(gameObject);
		}
	}
}

void SoldierBehaviour::SoldierMove(GameObject* move_node) {

	// get the for this function required components
	Movement* move_component = gameObject->GetComponent<Movement>();
	Node* node_component = move_node->GetComponent<Node>();

	// if the target node is the same it is already on or it is already occupied (position-check is needed because clicking a node twice with the same selected gameobject will make it unoccupied)
	if (move_component->target_position == move_node->transform.position || node_component->is_occupied) return;

	// make the clicked node occupied and the recent unoccupied
	node_component->is_occupied = true;

	if (old_node != nullptr) {
		old_node->GetComponent<Node>()->is_occupied = false;
	}

	// move the gameobject
	move_component->target_position = move_node->transform.position;
	travelling = true;

	// delete the gameobject from the recent stand
	for (size_t i = 0; i < stand->size(); i++) {
		if (stand->at(i) == gameObject) {
			stand->erase(stand->begin() + i);
			break;
		}
	}

	// used for accessing the recent stand and node
	this->stand = move_node->GetComponent<Node>()->stand;
	this->old_node = move_node;
}