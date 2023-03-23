#include "_Game.h"
#include "bullet.h"
#include "required/constants.h"
#include "required/functions.h"
#include "components/movement.h"

Bullet::Bullet(GameObject* target, GameObject* parent, bool is_hit, float damage) 
	:is_hit(is_hit), target(target), parent(parent), damage(damage)
{
	if (is_hit) {
		target_position = target->transform.position;
	}
	else {
		target_position.y = target->transform.position.y;
		target_position.x = target->transform.position.x + RandomF(min_inaccuracy, max_inaccuracy) * RandomInt(-1, 1);
	}
	//LOG_DEBUG("target_position: x:{0}, y:{1}", target_position.x, target_position.y);
}

Bullet::~Bullet() {
}

void Bullet::OnStart() {
	gameObject->AddComponent(new Movement(bullet_speed));
	gameObject->GetComponent<Movement>()->target_position = target_position;
}

void Bullet::OnStop() {
}

void Bullet::OnUpdate() {
	//LOG_DEBUG("transform.position: x:{0}, y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);
	if (gameObject->transform.position == target_position) {
		//LOG_DEBUG("Bullet at target position: x:{0}, y:{1}", gameObject->transform.position.x, gameObject->transform.position.y);
		if (is_hit) {
			LOG_DEBUG("bullet hit");
			if (target != nullptr) {
				// if he is dead
				if (target->GetComponent<Health>()->TakeDamage(damage)) {
					target = nullptr;
					if (parent->GetComponent<SoldierShooting>())
						parent->GetComponent<SoldierShooting>()->NullTarget();
					if (parent->GetComponent<EnemyShooting>())
						parent->GetComponent<EnemyShooting>()->NullTarget();
				}
			}
		}
		else { LOG_DEBUG("bullet not hit"); }
		
		delete gameObject;
		//LOG_DEBUG("Bullet deleted");
	}
}