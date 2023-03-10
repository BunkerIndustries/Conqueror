#include "bullet.h"
#include "required/constants.h"
#include "required/functions.h"
#include "components/movement.h"

Bullet::Bullet(GameObject* target, bool is_hit, float damage) 
	:is_hit(is_hit), target(target), damage(damage)
{
	if (is_hit) {
		target_position = target->transform.position;
	}
	else {
		target_position.y = target->transform.position.y;
		target_position.x = target->transform.position.x + RandomF(min_inaccuracy, max_inaccuracy) * RandomInt(-1, 1);
	}

	LOG_DEBUG("Bullet ctor()");
	LOG_DEBUG("target_position: x:{0}, y:{1}", target_position.x, target_position.y);
}

Bullet::~Bullet() {
	LOG_DEBUG("Bullet ~Bullet()");
}

void Bullet::start() {
	gameObject->AddComponent(new Movement(bullet_speed));
	gameObject->GetComponent<Movement>()->target_position = target_position;
	LOG_DEBUG("Bullet start()");
}

void Bullet::stop() {
	LOG_DEBUG("Bullet stop()");
}

void Bullet::update(float dt) {
	LOG_DEBUG("Bullet update()");
	LOG_DEBUG("transform.position: x:{0}, y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);
	if (gameObject->transform.position == target_position) {
		if (is_hit) {
			LOG_DEBUG("on target position");
			target->GetComponent<Health>()->TakeDamage(damage);
		}
		gameObject->Delete();
	}
}