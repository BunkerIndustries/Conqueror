#include "_Game.h"
#include "movement.h"
#include "required/functions.h"
#include "required/constants.h"

Movement::Movement(float movement_speed)
	:movement_speed(movement_speed)
{
	
}

void Movement::OnStart() {
	target_position = gameObject->transform.position;	// Do not move when initialised
	has_arrived = false;
	//LOG_DEBUG("Target x pos: {0}", target_position.x);
}

void Movement::OnStop() {

}

void Movement::OnUpdate() {

	if (target_position != gameObject->transform.position) {
		has_arrived = false;
		MoveTo(target_position, movement_speed);
	}
	else {
		has_arrived = true;
	}
}

void Movement::MoveTo(glm::vec2 target_pos, float speed) {

	glm::vec2 dir = target_pos - gameObject->transform.position;	// calculate direction (pos2 - pos1)
	//if (dir == glm::vec2(0.0f, 0.0f)) return;
	
	RoundVec2(dir);	  // round direction vector
	dir = glm::normalize(dir);
	//dir = glm::vec2(std::sqrtf(-(dir.x * dir.x)), -std::sqrtf(-(dir.y * dir.y)));	  // does not work
	
	
	gameObject->transform.position += dir * speed * Application::GetDT();

	RoundVec2(gameObject->transform.position);
	
}