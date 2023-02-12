#pragma once
#include "Engine.h"
#include "layers/ForegroundLayer.h"
#include <vector>
#include <random>

using namespace core;


// TODO: Change to vec2 2D-vector, cubes are placeholders for debugging and visualisation
inline std::vector<std::vector<GameObject*>> CreateGrid(const uint8_t x_size, const uint8_t y_size, const float offset, const glm::vec2 mid_pos, Layer *layer) {

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

			y_row.at(y)->addComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));	// add SpriteRenderer
			layer->AddGameObjectToLayer(y_row.at(y));
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