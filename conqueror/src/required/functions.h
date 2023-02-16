#pragma once
#include "Engine.h"
#include "layers/ForegroundLayer.h"
#include "required/constants.h"
#include "components/movement.h"
#include <vector>
#include <random>

using namespace core;


// TODO: Change to vec2 2D-vector, cubes are placeholders for debugging and visualisation
inline std::vector<std::vector<GameObject*>> CreateGrid(const uint8_t x_size, const uint8_t y_size, const float offset, const glm::vec2 mid_pos) {

	std::vector<std::vector<GameObject*>> grid;	//create 2D vector
	float cube_rad = 0.25f;
	glm::vec2 whole_len = glm::vec2(x_size * cube_rad * 2.0f + (x_size - 1) * offset, y_size * cube_rad * 2.0f + (y_size - 1) * offset);		//length of all cubes + offsets between
	glm::vec2 start_pos = glm::vec2(mid_pos.x - whole_len.x / 2.0f, mid_pos.y + whole_len.y / 2.0f);	// starts top left

	for (size_t x = 0; x < x_size; x++) {
		std::vector<GameObject*> y_row;	// create new y row vector 
		for (size_t y = 0; y < y_size; y++) {	
			y_row.push_back(new GameObject(std::to_string(x) + std::to_string(y), 
				Transform(glm::vec2(start_pos.x + x * (offset + 2.0f * cube_rad), start_pos.y - y * (offset + 2.0f * cube_rad)), 
				glm::vec2(2 * cube_rad))));	// add gameobjects to it

			y_row.at(y)->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));	// add SpriteRenderer
			y_row.at(y)->AddTag("move_node");
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


inline GameObject* CreateCharacter(std::string type, glm::vec2 spawn_pos) {
	float movement_speed;
	std::string sprite_path;
	GameObject* character = new GameObject(type, Transform(spawn_pos, character_scale));

	// set paths and movement speeds regarding the type of the character
	if (type == "soldier") { movement_speed = soldier_movement_speed; sprite_path = soldier_sprite_path; }
	else if (type == "medic") { movement_speed = medic_movement_speed; sprite_path = medic_sprite_path; }
	else if (type == "engineer") { movement_speed = engineer_movement_speed; sprite_path = engineer_sprite_path; }
	else LOG_DEBUG("WARNING: probably no valid 'type'-arg at CreateCharacter(); sofore movement_speed is not initialised");

	character->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));		// TODO: Change to sprite_paths
	character->AddComponent(new Movement(movement_speed));
	character->AddTag("character"); character->AddTag(type);

	foreground_layer->AddGameObjectToLayer(character);
	
	return character;
}