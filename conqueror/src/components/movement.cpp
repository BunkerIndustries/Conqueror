#include "movement.h"

Movement::Movement()
	:Component("movement")
{
	
}

void Movement::start() {
	target_pos = gameObject->transform.position;	// Do not move when initialised
}

void Movement::stop() {

}

void Movement::update(float dt) {
	MoveTo(target_pos, movement_speed);
}

void Movement::MoveTo(glm::vec2 target_pos, float speed) {

	glm::vec2 dir = glm::normalize(target_pos - gameObject->transform.position);
	
	LOG_DEBUG("x:{0} , y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);
	LOG_DEBUG(dir.x);
	gameObject->transform.position.x += dir.x * speed * Application::GetDT();
	gameObject->transform.position.y += dir.y * speed * Application::GetDT();
}