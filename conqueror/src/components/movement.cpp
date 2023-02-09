#include "movement.h"

Movement::Movement()
	:Component("movement")
{
	
}

void Movement::start() {
	target_pos = GameObject::CGMap[this]->transform.position;	// Do not move when initialised
}

void Movement::stop() {

}

void Movement::update(float dt) {
	MoveTo(target_pos, )
}

void Movement::MoveTo(glm::vec2 target_pos, float speed) {
	GameObject* go = GameObject::CGMap[this];	// get the gameobject the component is applied to
	glm::vec2 dir = glm::normalize(target_pos - go->transform.position);
	
	LOG_DEBUG("x:{0} , y:{1}", go->transform.position.x, go->transform.position.y);
	LOG_DEBUG(dir.x);
	while (go->transform.position.x != target_pos.x && go->transform.position.y != target_pos.y) {
		go->transform.position.x += dir.x * speed * Application::GetDT();
		go->transform.position.y += dir.y * speed * Application::GetDT();
		LOG_ERROR(go->transform.position.x);
	}
}