#include "health.h"

#include "required/constants.h"

Health::Health() {
	if (gameObject->HasTag("soldier")) {
		hp = soldier_health;
	}
	else if (gameObject->HasTag("medic")) {
		hp = medic_health;
	}
	else if (gameObject->HasTag("engineer")) {
		hp = engineer_health;
	}
	else LOG_DEBUG("Health not initialised");
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
	
	
	// delete this gameobject
}