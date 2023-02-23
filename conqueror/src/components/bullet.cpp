#include "bullet.h"
#include "required/constants.h"
#include "required/functions.h"
#include "components/movement.h"

Bullet::Bullet(GameObject* target, bool is_hit) 
	:is_hit(is_hit)
{
	if (is_hit) {
		target_position = target->transform.position;
	}
	else {
		target_position.y = target->transform.position.y;
		target_position.x = target->transform.position.x + RandomF(min_inaccuracy, max_inaccuracy) * RandomInt(-1, 1);	// + inaccuracy
	}
}

void Bullet::start() {
	gameObject->AddComponent(new Movement(bullet_speed));
	gameObject->GetComponent<Movement>()->target_position = target_position;

	gameObject->AddComponent(new SpriteRenderer(bullet_color));
	foreground_layer->AddGameObjectToLayer(gameObject);
}

void Bullet::stop() {

}

void Bullet::update(float dt) {
	if (gameObject->transform.position == target_position) {
		if (is_hit) {
			// target.MakeDamage()
		}
		delete gameObject;
	}
}