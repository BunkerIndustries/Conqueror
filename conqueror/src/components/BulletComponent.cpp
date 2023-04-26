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
		target->GetComponent<Health>()->TakeDamage(soldier_damage);
		delete gameObject;
	}

}

void BulletComponent::OnEvent(Event& event)
{
}
