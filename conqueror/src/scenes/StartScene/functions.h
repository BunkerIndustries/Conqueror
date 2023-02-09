#pragma once
#include "Engine.h"
#include "layers/ForegroundLayer.h"
#include <vector>

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
			std::cout << "x:" << std::to_string(x) << " y:" << std::to_string(y) << std::endl;
			std::cout << "xPos: " << std::to_string(start_pos.x + x * (offset + 2 * cube_rad)) << " yPos:" << std::to_string(start_pos.y + y * (offset + 2.0f * cube_rad)) << std::endl;
		}
		grid.emplace_back(y_row);	// add y_row to grid at index x
	}
	return grid;
}



//glm::vec2 CreateGrid(const uint8_t x_size, const uint8_t y_size, const float space, const glm::vec2 mid_pos) {
//
//}