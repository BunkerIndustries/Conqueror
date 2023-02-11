#include "movement.h"
#include "required/functions.h"

Movement::Movement()
	:Component("movement")
{
	
}

void Movement::start() {
	target_position = gameObject->transform.position;	// Do not move when initialised
	LOG_DEBUG("Target x pos: {0}", target_position.x);
	movement_speed = 1.0f;
}

void Movement::stop() {

}

void Movement::update(float dt) {
	MoveTo(target_position, movement_speed);
}

void Movement::MoveTo(glm::vec2 target_pos, float speed) {
	LOG_DEBUG("MoveTo called with target_pos={0},{1}", target_pos.x, target_pos.y);

	glm::vec2 dir = target_pos - gameObject->transform.position;	// calculate direction (pos2 - pos1)
	//RoundVec2(dir);		 // round direction vector
	
	dir = glm::vec2(std::sqrtf(-(dir.x * dir.x)), -std::sqrtf(-(dir.y * dir.y)));	// normalize vector (set length of vector to 1)
	
	LOG_DEBUG("dir_vector x:{0},y:{1}", dir.x, dir.y);
	LOG_DEBUG("x:{0} , y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);
	
	gameObject->transform.position.x += dir.x * speed * Application::GetDT();	// apply movement in direction with speed to x position
	gameObject->transform.position.y += dir.y * speed * Application::GetDT();	// apply movement in direction with speed to y position

	//RoundVec2(gameObject->transform.position);
}