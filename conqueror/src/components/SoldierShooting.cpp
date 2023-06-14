#include "_Game.h"
#include "SoldierShooting.h"
#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"



SoldierShooting::SoldierShooting() {

}

void SoldierShooting::OnStart() {
	//target = nullptr;
}

void SoldierShooting::OnStop() {
	
}

void SoldierShooting::OnUpdate() {

}

void SoldierShooting::Shoot() {
	
	for (uint8_t i = 0; i < max_soldier_lock_target_tries; i++) {
		GameObject* target = LockTarget();
		if (!target) continue;

		glm::vec2 distanceVec2 = target->transform.position - gameObject->transform.position;
		float dist = sqrt(distanceVec2.x * distanceVec2.x + distanceVec2.y * distanceVec2.y);

		glm::vec2 pos = target->transform.position;
		float distScale = dist / bulletInaccuracyMultiplicator;

		if (RandomInt(-dist, 4 + hit_probability_upgrade) < 0 && bulletDistanceMoreInaccuracy)
		{
			float randomX = RandomF(-1.0f, 1.0f) * distScale;
			pos.x += randomX;
		}

		
		gameScene->CreateBullet(gameScene->allyLayer, target, gameObject->transform.position, pos);
		
		break;
	}

}

GameObject* SoldierShooting::LockTarget() {
	// check if target already exists
	GameObject* target = GetTarget();
	if (target) {
		return target;
	}

	// choose a random row of enemies
	std::vector<GameObject*> enemies_in_row;
	int row = RandomInt(0, SumTo(enemy_grid_y));
	int prob = 0;
	for (int i = 1; i <= enemy_grid_y; i++) {
		prob += i;
		if (row <= prob) {
			row = i - 1;
			hit_probability = i;
			break;
		}
	}
	//LOG_TRACE(row);
	for (int i = 0; i < enemy_grid_x; i++) {
		if (enemy_stands[row][i]) {
			enemies_in_row.push_back(enemy_stands[row][i]);
		}
	}

	// if no enemies in row, return false
	if (enemies_in_row.empty()) {
		return nullptr;
	}

	// set random enemy in row as target and return true
	target = enemies_in_row[RandomInt(0, enemies_in_row.size() - 1)];
	ASSERT(target->HasTag("enemy"), "")
	Util::soldierTable[target].push_back(this);

	return target;
}

GameObject* SoldierShooting::GetTarget() const
{
	for (auto [key, val] : Util::soldierTable)
	{
		for (const SoldierShooting* ss : val)
		{
			if (ss == this) return key;
		}
	}
	return nullptr;
}

void SoldierShooting::UpgradeHitProbability() {
	hit_probability_upgrade += accuracy_upgrade_value * gameObject->GetComponent<SoldierBehaviour>()->GetLevel();
	gameObject->GetComponent<SoldierBehaviour>()->AddLevel();
}