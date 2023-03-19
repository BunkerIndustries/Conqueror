#pragma once
#include "Engine.h"
#include "layers/ForegroundLayer.h"
#include "required/constants.h"
#include "required/stands.h"
#include "components/movement.h"
#include "components/enemy_behaviour.h"
#include "components/node.h"
#include "components/enemy_shooting.h"
#include "components/soldier_shooting.h"
#include "components/soldier_behaviour.h"
#include "components/health.h"
#include "components/UI/character_ui.h"
#include <vector>
#include <random>

using namespace core;


// TODO: Change to vec2 2D-vector, cubes are placeholders for debugging and visualisation
inline std::vector<std::vector<GameObject*>> CreateEnemyGrid(const uint8_t x_size, const uint8_t y_size, const float offset, const glm::vec2 mid_pos) {

	std::vector<std::vector<GameObject*>> grid;	//create 2D vector
	float cube_rad = 0.25f;
	glm::vec2 whole_len = glm::vec2(x_size * cube_rad * 2.0f + (x_size - 1) * offset, y_size * cube_rad * 2.0f + (y_size - 1) * offset);		//length of all cubes + offsets between
	glm::vec2 start_pos = glm::vec2(mid_pos.x - whole_len.x / 2.0f, mid_pos.y + whole_len.y / 2.0f);	// starts top left

	for (size_t x = 0; x < x_size; x++) {
		std::vector<GameObject*> y_row;	// create new y row vector 
		for (size_t y = 0; y < y_size; y++) {	
			y_row.push_back(new GameObject(std::to_string(x) + std::to_string(y), 
				Transform(glm::vec2(start_pos.x + x * (offset + cube_rad * 2.0f), start_pos.y - y * (offset + 2.0f * cube_rad)), 
				glm::vec2(2 * cube_rad))));	// add gameobjects to it

			y_row.at(y)->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));	// add SpriteRenderer
			y_row.at(y)->AddComponent(new Node(nullptr));
			//y_row.at(y)->AddTag("move_node");
			foreground_layer->AddGameObjectToLayer(y_row.at(y));
		}
		grid.emplace_back(y_row);	// add y_row to grid at index x
	}
	return grid;
}

inline void RoundVec2(glm::vec2& vec) {		// written by chatGPT 0_0
	// rounds to 2 decimal places
	vec.x = std::roundf(vec.x * powf(10, 2)) / powf(10, 2);	
	vec.y = std::roundf(vec.y * powf(10, 2)) / powf(10, 2);
	
}

inline int RandomInt(const int from, const int to) {	// written by chatGPT 0_0
	
	std::random_device rd;  // Use a true random number source
	std::mt19937 generator(rd());  // Use Mersenne Twister algorithm
	std::uniform_int_distribution<> distribution(from, to);  // Distribute numbers evenly

	return distribution(generator);  // Generate the random number and return it
}

inline float RandomF(float min_float, float max_float) {	// written by chatGPT 0_0
	static bool initialized = false;
	if (!initialized) {
		srand(time(nullptr)); // set seed based on current time, only once
		initialized = true;
	}
	float random = ((float)rand()) / (float)RAND_MAX; // generate random float between 0 and 1
	float range = max_float - min_float; // calculate range
	return (random * range) + min_float; // scale and shift the random number to the desired range
}

inline int SumTo(int n) {
	return n * (n + 1) / 2;
}

inline GameObject* CreateCharacter(std::string type, glm::vec2 spawn_pos) {
	float movement_speed;
	float health;
	std::string sprite_path;
	GameObject* character_go = new GameObject(type, Transform(spawn_pos, character_scale));

	// set paths and movement speeds regarding the type of the character
	if (type == "soldier") { 

		movement_speed = soldier_movement_speed; sprite_path = soldier_sprite_path; 
		health = soldier_health;

		character_go->AddComponent(new SoldierBehaviour());
		character_go->AddComponent(new SoldierShooting());

	}
	else if (type == "medic") { 
		movement_speed = medic_movement_speed; sprite_path = medic_sprite_path; 
		health = medic_health;
	}
	else if (type == "engineer") { 
		movement_speed = engineer_movement_speed; sprite_path = engineer_sprite_path; 
		health = engineer_health;
	}
	else LOG_WARN("WARNING: probably no existing type given when creating a character");

	character_go->AddTag(type);
	character_go->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));		// TODO: Change to sprite_path
	character_go->AddComponent(new Movement(movement_speed));
	character_go->AddComponent(new Health(health));
	character_go->AddComponent(new CharacterUI());

	foreground_layer->AddGameObjectToLayer(character_go);

	return character_go;
}

inline GameObject* CreateEnemy(std::string name, glm::vec2 spawn_pos) {
	GameObject* enemy_go = new GameObject(name, Transform(spawn_pos, enemy_scale));

	enemy_go->AddTag("enemy");
	enemy_go->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));		// TODO: Change to sprite_path
	enemy_go->AddComponent(new Movement(enemy_movement_speed));
	enemy_go->AddComponent(new EnemyBehaviour());
	enemy_go->AddComponent(new EnemyShooting());
	enemy_go->AddComponent(new Health(enemy_health));
	
	foreground_layer->AddGameObjectToLayer(enemy_go);

	return enemy_go;
}

inline GameObject* CreateNode(glm::vec2 position, Stand& node_stand) {
	GameObject* node_go = new GameObject("node", Transform(position, node_size));

	node_go->AddComponent(new SpriteRenderer(*node_stand.color));
	node_go->AddComponent(new Node(node_stand.stand));

	if(node_stand.stand != waiting_stand.stand) node_go->AddTag("move_node");
	else {
		waiting_nodes.push_back(node_go);
	}
	
	foreground_layer->AddGameObjectToLayer(node_go);

	return node_go;
}

inline GameObject* CreateBuilding(glm::vec2 position, std::string type) {
	
	GameObject* building = new GameObject(type + "-building", Transform(position, building_size));

	if (type == "medic") {
		building->AddComponent(medic_management);
		building->AddComponent(new SpriteRenderer(glm::vec4(0.05f, 0.05f, 0.05f, 1.0f)));	// temp: replace with correct sprite-path
	}
	else if (type == "engineer") {

	}
	else {
		LOG_DEBUG("WARNING: probably no existing type given when creating a building");
	}
	
	foreground_layer->AddGameObjectToLayer(building);

	return building;
}