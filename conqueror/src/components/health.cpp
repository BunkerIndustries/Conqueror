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

void Health::TakeDamage(float damage) {
	hp -= damage;
	if (hp <= 0.0f) Die();
}

void Health::Die() {
	gameObject->Delete();
}