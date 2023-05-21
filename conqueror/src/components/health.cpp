#include "_Game.h"
#include "health.h"

#include "required/constants.h"
#include "utils\Supply.h"


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
	hp -= damage;
	if (hp <= 0.0f) {
		if (gameScene->GetActiveCharacter() == gameObject) gameScene->SetActiveCharacter(nullptr);
		if (gameObject->HasTag("soldier")) {
			// get node and unoccupy it
			gameObject->GetComponent<SoldierBehaviour>()->FreeNode();
			gameScene->uiLayer->DeactivateCharacterUI();
			Util::enemyTable.erase(Util::enemyTable.find(gameObject));
			gameScene->mapLayer->CreateDeadBody("Anims/Soldier/soldier_dead.png", gameObject->transform.position);
			Supply::CheckForGameOver();

		}
		else if (gameObject->HasTag("enemy"))
		{
			if (gameObject->GetComponent<EnemyBehaviour>()->GetNode() != nullptr)
				gameObject->GetComponent<EnemyBehaviour>()->GetNode()->GetComponent<Node>()->is_occupied = false;
			if (Util::soldierTable.count(gameObject))
			{
				auto it = Util::soldierTable.find(gameObject);
				ASSERT(!(*it).first->IsDeleted(), "")
				Util::soldierTable.erase(it);
			}
			gameScene->mapLayer->CreateDeadBody("Anims/Enemy/french_dead.png", gameObject->transform.position);

			gameScene->waveManager->CheckForEnemiesDead();
		}
		delete gameObject;
		return true;
	}
	return false;
	// return true means dead
}

float Health::GetHp() { return hp; }

void Health::GetHealed() {
	hp = soldier_health;
}