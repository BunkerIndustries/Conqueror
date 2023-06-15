#include "_Game.h"
#include "BulletComponent.h"

#include "Movement.h"

Shr<Sound> BulletComponent::sound_mg;

void BulletComponent::Init()
{
	sound_mg = MakeShr<Sound>();
	sound_mg->LoadSound("assets/sounds/mg_bullet.wav");
}

static bool CoordRoundVec2(glm::vec2 targetPos, glm::vec2 pos)
{
	glm::vec2 diff = { targetPos.x - pos.x, targetPos.y - pos.y };
	if (abs(diff.x) < 0.25f && abs(diff.y) < 0.25f) return true;
	return false;
}

BulletComponent::BulletComponent(GameObject* target, glm::vec2 pos)
	: target(target), pos(pos)
{
	if (target == nullptr)
	{
		sound_mg->SoundPlay();
	}
}

void BulletComponent::OnStart()
{

}

void BulletComponent::OnStop()
{

}

void BulletComponent::OnUpdate()
{
	bool del = false;
	Movement* movement = gameObject->GetComponent<Movement>();
	gameObject->transform.rotation = -Util::VectorAngle(movement->GetDirection());
	if (target == nullptr)
	{
		for (auto vec : enemy_stands)
		{
			for (auto* gm : vec)
			{
				if (gm != nullptr && gm->GetComponent<Health>() != nullptr && CoordRoundVec2(gameObject->transform.position, gm->transform.position))
				{
					gm->GetComponent<Health>()->TakeDamage(mg_damage + mg_damage_upgrade);
					delete gameObject;
					return;
				}
			}
		}
	}
	
	if (movement->IsArrived())
	{
		if (target != nullptr && gameObject->transform.position == target->transform.position)
		{
			if (target->HasTag("enemy"))
				target->GetComponent<Health>()->TakeDamage(soldier_damage + damage_upgrade);
			if (target->HasTag("soldier"))
				target->GetComponent<Health>()->TakeDamage(enemy_damage - armor_upgrade);
		}
		delete gameObject;
	}
}

void BulletComponent::OnEvent(Event& event)
{
}
