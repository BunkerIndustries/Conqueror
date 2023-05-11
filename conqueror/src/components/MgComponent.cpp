#include "_Game.h"

#include "MgComponent.h"
#include "required/functions.h"
#include "required/stands.h"

MgComponent::MgComponent(GameObject* own_node) 
	:own_node(own_node->GetComponent<Node>())
{
}

void MgComponent::OnStart() {
	target = nullptr;
	dt_counter = 0.0f;
	ammo = mg_magazin_size;
}

void MgComponent::OnStop() {

}

void MgComponent::OnUpdate() {
	
	if (!own_node->contains_soldier) return;

	dt_counter += Application::GetDT();

	if (ammo <= 0) {
		if (dt_counter >= mg_reload_time * game_time_factor) {
			ammo = mg_magazin_size;
			dt_counter = 0.0f;
		}
		return;
	}

	if (target == nullptr) {
		LockTarget();
		return;
	}

	if (dt_counter < mg_shoot_interval * game_time_factor) {
		return;
	}

	// shoot
	dt_counter = 0.0f;
	ammo -= 1;
	glm::vec2 distanceVec2 = target->transform.position - gameObject->transform.position;
	float dist = sqrt(distanceVec2.x * distanceVec2.x + distanceVec2.y * distanceVec2.y);

	glm::vec2 pos = target->transform.position;
	float distScale = dist / bulletInaccuracyMultiplicator;

	if (RandomInt(-dist, 2) < 0 && bulletDistanceMoreInaccuracy)
	{
		float randomX = RandomF(-1.0f, 1.0f) * distScale;
		pos.x += randomX;
	}

	gameScene->CreateBullet(gameScene->allyLayer, target, gameObject->transform.position, pos);
}

GameObject* MgComponent::LockTarget() {

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

GameObject* MgComponent::GetTarget() const
{
	for (auto [key, val] : Util::soldierTable)
	{
		for (const MgComponent* ss : val)
		{
			if (ss == this) return key;
		}
	}
	return nullptr;
}