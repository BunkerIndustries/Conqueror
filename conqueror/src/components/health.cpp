#include "health.h"

#include "required/constants.h"

Health::Health(float hp) 
	:hp(hp)
{
	
}

void Health::start() {

}

void Health::stop() {

}

void Health::update(float dt) {

}

bool Health::TakeDamage(float damage) {
	if (this == nullptr) return true;
	hp -= damage;
	if (hp <= 0.0f) {
		gameObject->Delete();
		LOG_DEBUG("gameobject deleted");
		return true;
	}
	return false;
	// return true means dead
}
