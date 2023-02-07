#pragma once
#include "Engine.h"
#include <vector>

using namespace core;

GameObject* CreateGrid(const uint8_t x_size, const uint8_t y_size, const float space, const glm::vec2 mid_pos) {
	std::vector<std::vector<GameObject>> *grid = new std::vector<std::vector<GameObject>>;	//create 2D vector on the heap
	for (size_t x = 0; x < x_size; x++) {
		std::vector<GameObject> *y_row = new std::vector<GameObject>;	// create new y row vector 
		for (size_t y = 0; y < y_size; y++) {	
			y_row->push_back(GameObject("", Transform(glm::vec2(), glm::vec2())));	// add gameobjects to it
			y_row->at(y).addComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));	// add SpriteRenderer
		}
		grid->at(x).push_back(*y_row);	// add y_row to grid at index x
	}
}