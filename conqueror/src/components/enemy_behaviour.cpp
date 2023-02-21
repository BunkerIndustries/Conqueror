#include "enemy_behaviour.h"

#include "required/constants.h"
#include "required/functions.h"
#include "components/movement.h"


EnemyBehaviour::EnemyBehaviour() {

}


void EnemyBehaviour::start() {
	move_component = gameObject->GetComponent<Movement>();

	dt_time_counter = 0.0f;

	is_waiting = false;
	time_over = true;
	time_running = false;

	size_t random_x_pos = RandomInt(0, enemy_grid_x - 1);
	move_component->target_position = enemy_grid.at(random_x_pos).at(0)->transform.position;
	y_index = 0;
	x_index = random_x_pos;
}

void EnemyBehaviour::stop() {

}

void EnemyBehaviour::update(float dt) {

	// handles the complete movement and shoot behaviour of the enemies 
	if (is_waiting) {
		dt_time_counter += dt;
		if (time_over) {
			is_waiting = false;
			time_running = false;

			if (y_index != enemy_grid_y - 1) {
				ChoosePosAndMove();
			}
			
		}
		else {
			if (!time_running) {
				time_over = false;
				time_running = true;

				// random calculation of time to wait
				time_to_wait = RandomF(min_enemy_waiting_time, max_enemy_waiting_time) * enemy_waiting_time_factor;
				LOG_DEBUG("time_to_wait: {0}", time_to_wait);
			}
			else {
				if (dt_time_counter >= time_to_wait) {
					time_over = true;
					dt_time_counter = 0.0f;

					// shoot
				}
			}
			
		}
	}
	else {
		if (gameObject->transform.position == move_component->target_position) {
			is_waiting = true;
			time_over = false;
		}
	}

}


void EnemyBehaviour::ChoosePosAndMove() {

	// first calculate random number between 0 and enemy_random_movement_sum to select the position the enemy should move to, based on their probabilities
	uint8_t random = RandomInt(0, enemy_random_movement_sum);
	
	// if he is at the bottom of the grid, do nothing
	if (y_index == enemy_grid_y - 1) return;

	GameObject* move_node_go;

	// calculates the probabilities for each move-possibility and sets the move_node_go to the randomly selected node
	if (random <= enemy_move_left_probability && x_index != 0) {
		move_node_go = enemy_grid.at(x_index - 1).at(y_index + 1);
		x_index -= 1;
		y_index += 1;
	}
	else if (random <= enemy_move_left_probability + enemy_move_right_probability && x_index != enemy_grid_x - 1) {
		move_node_go = enemy_grid.at(x_index + 1).at(y_index + 1);
		x_index += 1;
		y_index += 1;
	}
	else{
		move_node_go = enemy_grid.at(x_index).at(y_index + 1);
		y_index += 1;
	}

	// if this node is already occupied, do nothing
	if (move_node_go->GetComponent<Node>()->is_occupied) return;

	// now move to the selected node and occupy it
	move_component->target_position = move_node_go->transform.position;
	enemy_grid.at(x_index).at(y_index)->GetComponent<Node>()->is_occupied = true;

}