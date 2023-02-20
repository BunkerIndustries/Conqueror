#include "enemy_behaviour.h"

#include "required/constants.h"
#include "required/functions.h"
#include "components/movement.h"


EnemyBehaviour::EnemyBehaviour() {

}


Movement* move_component;	// not in header file because of avoidable include
void EnemyBehaviour::start() {
	move_component = gameObject->GetComponent<Movement>();

	dt_time_counter = 0.0f;

	is_waiting = true;
	time_over = true;
	time_running = false;
}

void EnemyBehaviour::stop() {

}

void EnemyBehaviour::update(float dt) {
	
	if (is_waiting) {
		dt_time_counter += dt;
		if (time_over) {
			is_waiting = false;
			time_running = false;

			// choose random pos (update later)
			move_component->target_position = enemy_grid.at(RandomInt(0, enemy_grid_x - 1)).at(RandomInt(0, enemy_grid_y - 1))->transform.position;
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

