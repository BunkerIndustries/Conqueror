#include "movement.h"
#include "required/functions.h"
#include "required/constants.h"

Movement::Movement(float movement_speed)
	:movement_speed(movement_speed)
{
	
}

void Movement::start() {
	target_position = gameObject->transform.position;	// Do not move when initialised
	has_arrived = false;
	//LOG_DEBUG("Target x pos: {0}", target_position.x);
}

void Movement::stop() {

}

void Movement::update(float dt) {

	if (target_position != gameObject->transform.position) {
		has_arrived = false;
		MoveTo(target_position, movement_speed);
	}
	else {
		has_arrived = true;
	}
}

void Movement::MoveTo(glm::vec2 target_pos, float speed) {
	//LOG_DEBUG("MoveTo called with target_pos={0},{1}", target_pos.x, target_pos.y);

	glm::vec2 dir = target_pos - gameObject->transform.position;	// calculate direction (pos2 - pos1)
	//if (dir == glm::vec2(0.0f, 0.0f)) return;
	
	RoundVec2(dir);	  // round direction vector
	dir = glm::normalize(dir);
	//dir = glm::vec2(std::sqrtf(-(dir.x * dir.x)), -std::sqrtf(-(dir.y * dir.y)));	  // does not work
	
	/*LOG_DEBUG("dir_vector x:{0},y:{1}", dir.x, dir.y);
	LOG_DEBUG("x:{0} , y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);*/
	
	gameObject->transform.position += dir * speed * Application::GetDT();

	//gameObject->transform.position.x += dir.x * speed * Application::GetDT();	// apply movement in direction with speed to x position
	//gameObject->transform.position.y += dir.y * speed * Application::GetDT();	// apply movement in direction with speed to y position
	RoundVec2(gameObject->transform.position);

	//RoundVec2(gameObject->transform.position);
}