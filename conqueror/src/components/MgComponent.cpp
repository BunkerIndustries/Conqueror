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
	glm::vec2 end_point;

	int r = RandomInt(0, enemy_grid_y + mg_miss_points);
	if (r <= hit_probability) {
		end_point = target->transform.position;
		if (target->GetComponent<Health>()->TakeDamage(mg_damage)) {
			target = nullptr;
		}
	}
	else {
		end_point = glm::vec2(target->transform.position.x + RandomF(min_inaccuracy, max_inaccuracy) * RandomInt(-1, 1), target->transform.position.y);
	}

	GameObject* trace = new GameObject("bullet", Transform());
	trace->AddComponent(new LineRenderer(gameObject->transform.position, end_point, trace_color, trace_thickness, trace_lasting * game_time_factor));
	gameScene->allyLayer->AddGameObjectToLayer(trace);
}

void MgComponent::LockTarget() {

	std::vector<GameObject*> enemy_row_vec;

	// used for choosing the enemy-row randomly
	int random = RandomInt(0, SumTo(enemy_grid_y));
	size_t prob = 0;

	// choose 1 random row of the enemy grid
	int y_row = 0;
	for (uint8_t i = 1; i <= enemy_grid_y; i++) {
		prob += i;
		if (random <= prob) {
			y_row = i - 1;
			hit_probability = i;
			break;
		}
	}

	// copy all enemies who are in the randomly chosen row into another vector
	for (size_t i = 0; i < enemy_grid_x; i++) {
		if (enemy_stands[y_row][i] != nullptr) enemy_row_vec.push_back(enemy_stands[y_row][i]);
	}


	// if this vector contains no enemies => no target is set, try unsuccessful
	if (enemy_row_vec.size() == 0) {
		return;
	}
	// if it contains enemies => a target is set, try successful
	target = enemy_row_vec.at(RandomInt(0, enemy_row_vec.size() - 1));
}