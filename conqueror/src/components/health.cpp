#include "_Game.h"
#include "health.h"

#include "required/constants.h"

Health::Health(float hp) 
	:hp(hp)
{
	
}

void Health::OnStart() {

}

void Health::OnStop() {

}

void Health::OnUpdate() {

}

bool Health::TakeDamage(float damage) {
	if (this == nullptr) return true;
	hp -= damage;
	if (hp <= 0.0f) {
		delete gameObject;
		LOG_DEBUG("gameobject deleted");
		return true;
	}
	return false;
	// return true means dead
}

float Health::GetHp() { return hp; }

void Health::GetHealed() {
	hp = soldier_health;
}