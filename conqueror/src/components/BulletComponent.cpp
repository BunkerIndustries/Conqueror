#include "_Game.h"
#include "BulletComponent.h"

#include "Movement.h"

BulletComponent::BulletComponent(GameObject* target, glm::vec2 pos)
	: target(target), pos(pos)
{

}

void BulletComponent::OnStart()
{
}

void BulletComponent::OnStop()
{
}

void BulletComponent::OnUpdate()
{
	Movement* movement = gameObject->GetComponent<Movement>();
	gameObject->transform.rotation = Util::VectorAngle(movement->GetDirection().y, movement->GetDirection().x);
	if (movement->IsArrived())
	{
		if (gameObject->transform.position == target->transform.position)
		{
			if (target->HasTag("enemy"))
				target->GetComponent<Health>()->TakeDamage(soldier_damage);
			if (target->HasTag("soldier"))
				target->GetComponent<Health>()->TakeDamage(enemy_damage);
		}
		delete gameObject;
	}

}

void BulletComponent::OnEvent(Event& event)
{
}
