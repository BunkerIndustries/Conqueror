#include "soldier_behaviour.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

#include "soldier_shooting.h"


SoldierBehaviour::SoldierBehaviour() 
{

}

void SoldierBehaviour::start() {

	// start configuration
	on_spawn_pos = true;
	travelling = false;
	time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time) * waiting_time_factor;
	dt_counter = 0.0f;
}

void SoldierBehaviour::stop() {
	// delete the gameobject from the recent stand
	for (size_t i = 0; i < stand->size(); i++) {
		if (stand->at(i) == gameObject) {
			stand->erase(stand->begin() + i);
			break;
		}
	}
}

void SoldierBehaviour::update(float dt) {
	
	// if he's not walking
	if (!travelling) {

		// if he is not on the waiting stand
		if (this->stand != waiting_stand.stand) {

			// if time is not over => increase dt-time-counter by dt
			if (!(dt_counter >= time_to_wait)) {
				dt_counter += dt;
				//ld("dt_counter: {0} ; time_to_wait: {1}", dt_counter, time_to_wait);
			}

			// if time is over => not on waiting stand (gameobject shoots and the waiting time get's calculated again)
			//					  on waiting stand     (soldier tries to move to a waiting node => if that's not possible => repeat waiting and check next time again
			else {
				if (on_spawn_pos) {
					if (SoldierTryMoveToWaitingNode()) {
						on_spawn_pos = false;
					}
					else {
						RestartTimer();
					}
				}
				else {
					gameObject->GetComponent<SoldierShooting>()->Shoot();
					RestartTimer();
				}
				
			}
		}
	}

	// if he arrived at the new node => the stand the node it's in get's extended by the gameobject
	else {
		/*if (gameObject->GetComponent<Movement>()->has_arrived) {
			travelling = false;
			this->stand->push_back(gameObject);
		}*/
		if (gameObject->transform.position == target_position) {
			travelling = false;
			this->stand->push_back(gameObject);
			RestartTimer();
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

	old_node->GetComponent<Node>()->is_occupied = false;

	// move the gameobject
	move_component->target_position = move_node->transform.position;
	this->target_position = move_node->transform.position;
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

bool SoldierBehaviour::SoldierTryMoveToWaitingNode() {

	// choose a free waiting node
	for (auto node : waiting_nodes) {
		if (!node->GetComponent<Node>()->is_occupied) {

			// move the gameobject to the chosen waiting node 
			gameObject->GetComponent<Movement>()->target_position = node->transform.position;
			this->target_position = node->transform.position;
			node->GetComponent<Node>()->is_occupied = true;
			this->stand = waiting_stand.stand;
			this->stand->push_back(gameObject);
			this->old_node = node;

			return true;
		}
	}
	return false;
}

void SoldierBehaviour::RestartTimer() {
	dt_counter = 0.0f;
	time_to_wait = RandomF(min_soldier_shoot_waiting_time, max_soldier_shoot_waiting_time) * waiting_time_factor;
}