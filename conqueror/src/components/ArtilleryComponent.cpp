#include "_Game.h"

#include "ArtilleryComponent.h"
#include "required/constants.h"
#include "required/functions.h"

ArtilleryComponent::ArtilleryComponent() {

}

void ArtilleryComponent::OnStart() {

}

void ArtilleryComponent::OnStop() {

}

void ArtilleryComponent::OnUpdate() {
	dt_counter += Application::GetDT();

	// TODO: random time
	if (dt_counter >= artillery_shoot_interval) {
		Shoot();
		dt_counter = 0.0f;
	}
}

// makes damage in ring form
void ArtilleryComponent::Shoot() {
	// choose a random middle-node at the enemy grid
	uint8_t x = RandomInt(0, enemy_grid_x - 1);
	uint8_t y = RandomInt(0, enemy_grid_y - 1);
	GameObject* target_node = enemy_grid.at(x).at(y);

	GameObject* nuclear_bomb_explosion = new GameObject("boom", Transform(target_node->transform.position, artillery_explosion_size), ProjectionMode::PERSPECTIVE);
	nuclear_bomb_explosion->AddComponent(new SpriteRenderer(glm::vec4(0.8f, 1.0f, 1.0f, 1.0f), Geometry::RECTANGLE));	// TODO: use sprite
	
	glm::ivec2 top_left = glm::ivec2(x - 1, y + 1);
	// loops through a field that starts at the top left of the randomly chosen middle-node
	for (uint8_t x = 0; x < 3; x++) {

		// if out of x-bounds 
		if (top_left.x < 0 || top_left.x + x > enemy_grid_x - 1) continue;
		for (uint8_t y = 0; y < 3; y++) {

			// if out ob y-bounds
			if (top_left.y < 0 || top_left.y + > enemy_grid_y+1) continue;

			// make damage to every gameobject in this field
			GameObject* hit_enemy = enemy_grid[top_left.x + x][top_left.y + y];
			if (hit_enemy != nullptr) {
				// crit hit on enemies that stand on the middle-node
				if (x == 1 && y == 1) {
					hit_enemy->GetComponent<Health>()->TakeDamage(artillery_critical_damage);
				}
				else {
					hit_enemy->GetComponent<Health>()->TakeDamage(artillery_normal_damage);
				}
			}
		}
	}
}