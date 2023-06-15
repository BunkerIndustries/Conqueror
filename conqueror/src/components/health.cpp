#include "_Game.h"
#include "health.h"
#include "EnemyBehaviour.h"

#include "required/constants.h"
#include "utils/Supply.h"
#include "utils/Economy.h"

Shr<Sound> Health::death;
Shr<Sound> Health::death_special;
Shr<Sound> Health::hit_soldier;
Shr<Sound> Health::hit_enemy;

Health::Health(float hp) 
	:hp(hp)
{
	

}


void Health::Init()
{
	death = MakeShr<Sound>();
	death_special = MakeShr<Sound>();
	hit_soldier = MakeShr<Sound>();
	hit_enemy = MakeShr<Sound>();


	hit_soldier->LoadSound("assets/sounds/soldier_damage.wav");
	hit_enemy->LoadSound("assets/sounds/enemy_damage.wav");

	death->LoadSound("assets/sounds/death.wav");
	death_special->LoadSound("assets/sounds/enemy_death_special.wav");
}

void Health::OnStart() {

}

void Health::OnStop() {

}

void Health::OnUpdate() {
	if (!just_hit) return;
	dt_counter += Application::GetDT();
	if (dt_counter > show_hit_time) {
		just_hit = false;
		gameObject->GetComponent<SpriteSheet>()->ChangeColor(white_color);
		dt_counter = 0.0f;
	}
}

bool Health::TakeDamage(float damage) {
	hp -= damage;
	just_hit = true;
	if (gameObject->HasTag("soldier"))
	{
		hit_soldier->SoundPlay();
	}
	else
	{
		hit_enemy->SoundPlay();
	}
	
	gameObject->GetComponent<SpriteSheet>()->ChangeColor(hit_color);
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

			death->SoundPlay();
		}
		else if (gameObject->HasTag("enemy"))
		{
			Economy::AddBalance(2);
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

			int tmp = Utils::randRange(0, 5);
			if (tmp == 3)
			{
				death_special->SoundPlay();
			}
			else
			{
				
			}
			death->SoundPlay();
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