#include "_Game.h"
#include "soldier_shooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"

std::unordered_map<SoldierShooting*, GameObject*> SoldierShooting::trackTable;

SoldierShooting::SoldierShooting() {

}

void SoldierShooting::OnStart() {
	target = nullptr;
}

void SoldierShooting::OnStop() {
	
}

void SoldierShooting::OnUpdate() {

}

void SoldierShooting::Shoot() {
	
	for (uint8_t i = 0; i < max_soldier_lock_target_tries; i++) {
		if (!LockTarget()) continue;
		gameScene->CreateBullet(gameScene->allyLayer, gameObject->transform.position, glm::vec2(10.0f, 0.0f));
		break;
	}

}

bool SoldierShooting::LockTarget() {
	return true;
}

void SoldierShooting::UnlockTarget(GameObject* target) const
{
	for (auto& [key, val] : trackTable)
	{
		if (val == target)
		{
			key->NullTarget();
		}
	}
}
