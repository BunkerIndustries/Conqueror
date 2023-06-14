#include "_Game.h"
#include "health.h"
#include "EnemyBehaviour.h"

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
	dt_counter += Application::GetDT();
	if (!just_hit) return;
	if (dt_counter > show_hit_time) {
		just_hit = false;
		gameObject->GetComponent<SpriteRenderer>()->SetColor(white_color);
		dt_counter = 0.0f;
	}
}

bool Health::TakeDamage(float damage) {
	hp -= damage;
	just_hit = true;
	//gameObject->GetComponent<SpriteSheet>()->ChangeColor(hit_color);
	if (gameScene->GetActiveCharacter() == gameObject) {
		gameScene->uiLayer->DeactivateCharacterUI();
		if (gameObject->HasTag("soldier")) {
			gameScene->uiLayer->ActivateSoldierUI();
		}
		else if (gameObject->HasTag("medic")) {
			gameScene->uiLayer->ActivateMedicUI();
		}
		else if (gameObject->HasTag("engineer")) {
			gameScene->uiLayer->ActivateEngineerUI();
		}
	}
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
			if(gameObject->GetComponent<EnemyBehaviour>()->GetXIndex()){
				filled_last_row_grid_positions.remove(gameObject->GetComponent<EnemyBehaviour>()->GetXIndex());
			}
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