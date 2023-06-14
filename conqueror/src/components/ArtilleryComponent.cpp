#include "_Game.h"

#include "ArtilleryComponent.h"
#include "required/constants.h"
#include "required/functions.h"
#include "components/SingleAnimationComponent.h"
#include "components/DestroyOverTime.h"

ArtilleryComponent::ArtilleryComponent(GameObject* own_node) 
	:own_node(own_node->GetComponent<Node>())
{
	dt_counter = 0.0f;
}

void ArtilleryComponent::OnStart() {
	reload_time = RandomF(artillery_min_reload_time, artillery_max_reload_time) * game_time_factor;
	LOG_DEBUG("reload_time: {0}", reload_time);
}

void ArtilleryComponent::OnStop() {

}

void ArtilleryComponent::OnUpdate() {

	if (!own_node->contains_soldier) return;

	dt_counter += Application::GetDT();
	if (dt_counter >= reload_time) {
		Shoot();
		dt_counter = 0.0f;
	}
}

// makes damage in ring form
void ArtilleryComponent::Shoot() {
	// choose a random middle-node at the enemy grid
	uint8_t target_x = RandomInt(0, enemy_grid_x - 1);
	uint8_t target_y = RandomInt(0, enemy_grid_y - 1);
	GameObject* target_node = enemy_grid.at(target_x).at(target_y);

	//gameObject->GetComponent<SingleAnimation>()->PlayAnimation(true);
	LOG_DEBUG("ARTILLERY SHOOT");

	//GameObject* explosionb = new GameObject("bum", Transform(target_node->transform.position, artillery_explosion_size), ProjectionMode::PERSPECTIVE);
	//explosionb->AddComponent(new SpriteRenderer(glm::vec4(white_color), Geometry::RECTANGLE));
	//explosionb->AddComponent(new DestroyOverTime(artillery_explosion_lasting));
	//gameScene->allyLayer->AddGameObjectToLayer(explosionb);

	GameObject* explosion = new GameObject("bum", Transform(target_node->transform.position, artillery_explosion_size), ProjectionMode::PERSPECTIVE);
	explosion->AddComponent(new SingleAnimation(DataPool::GetTexture("Anims/artillery_explosion.png"), 136.0f, 136.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), artillery_explosion_anim_speed, glm::vec2(0.0f, 0.0f), DataPool::GetTexture("Anims/artillery_explosion.png"), 1.0f, 1.0f, 1.0f, 1.0f));
	//explosion->AddComponent(new DestroyOverTime(artillery_explosion_lasting));
	gameScene->allyLayer->AddGameObjectToLayer(explosion);
	explosion->GetComponent<SingleAnimation>()->PlayAnimation(true);
	shoot.LoadSound("assets/sounds/artillery.wav");
	shoot.SoundPlay();
	glm::ivec2 top_left = glm::ivec2(target_x - 1, target_y - 1);
	// loops through a field that starts at the top left of the randomly chosen middle-node
	for (uint8_t x = 0; x < 3; x++) {

		// if out of x-bounds 
		if (top_left.x < 0 || top_left.x + x >= enemy_grid_x) continue;
		for (uint8_t y = 0; y < 3; y++) {

			// if out ob y-bounds
			if (top_left.y < 0 || top_left.y + y >= enemy_grid_y) continue;

			// make damage to every gameobject in this field
			int actual_x = top_left.x + x;
			int actual_y = top_left.y + y;
			GameObject* hit_enemy = enemy_stands[actual_y][actual_x];
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
	reload_time = RandomF(artillery_min_reload_time, artillery_max_reload_time) * game_time_factor;
}