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

	if (dt_counter >= artillery_shoot_interval) {
		Shoot();
		dt_counter = 0.0f;
	}
}

void ArtilleryComponent::Shoot() {
	uint8_t x = RandomInt(0, enemy_grid_x - 1);
	uint8_t y = RandomInt(0, enemy_grid_y - 1);
	GameObject* target_node = enemy_grid.at(x).at(y);

	GameObject* nuclear_bomb_explosion = new GameObject("boom", Transform(target_node->transform.position, artillery_explosion_size), ProjectionMode::PERSPECTIVE);
	nuclear_bomb_explosion->AddComponent(new SpriteRenderer(glm::vec4(0.8f, 1.0f, 1.0f, 1.0f), Geometry::RECTANGLE));	// TODO: use sprite
	
	glm::ivec2 top_left = glm::ivec2(x - 1, y + 1);
	for (uint8_t x = 0; x < 3; x++) {
		if (top_left.x < 0 || top_left.x > enemy_grid_x - 1) continue;
		for (uint8_t y = 2; y >= 0; y--) {
			if (top_left.y - y < 0) continue;
			// enemy stands
		}
	}
	// make damage in ring-form
}