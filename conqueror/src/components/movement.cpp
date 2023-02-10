#include "movement.h"
#include "required/functions.h"

Movement::Movement()
	:Component("movement")
{
	
}

void Movement::start() {
	target_pos = gameObject->transform.position;	// Do not move when initialised
	LOG_DEBUG("Target x pos: {0}", target_pos.x);
	movement_speed = 0.1f;
}

void Movement::stop() {

}

void Movement::update(float dt) {
	MoveTo(target_pos, movement_speed);
}

// TODO: dir bevor addition auf 2 nachkommastellen runden 
void Movement::MoveTo(glm::vec2 target_pos, float speed) {
	LOG_DEBUG("MoveTo called with target_pos={0},{1}", target_pos.x, target_pos.y);
	glm::vec2 dir = target_pos - gameObject->transform.position;
	dir = glm::vec2(-std::sqrtf(dir.y * dir.y) + 1, -std::sqrtf(dir.x * dir.x) + 1);	// normalize vector (set length of vector to 1)
	RoundVec2(dir);
	LOG_DEBUG("dir_vector x:{0},y:{1}", dir.x, dir.y);
	LOG_DEBUG("x:{0} , y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);
	gameObject->transform.position.x += dir.x * speed * Application::GetDT();
	gameObject->transform.position.y += dir.y * speed * Application::GetDT();
}