#pragma once
#include "Engine.h"
#include "stands.h"
#include "functions.h"
#include <utility>
#include <vector>


inline void CreateGameMap(std::vector<std::pair<std::vector<glm::vec2>, Stand>>& stands_with_nodes) {
	// for every stand (vector of its node-positions)
	for (auto& node : stands_with_nodes) {

		Stand s = node.second;

		// for every node-position in that stand
		for (auto& pos : node.first) {
			// create a node belonging to the stand with the desired position
			GameObject* n = CreateNode(pos, s);
		}
	}
}

inline std::vector<std::pair<std::vector<glm::vec2>, Stand>> standard_map = {
	{
		{
			glm::vec2(0.0f, 1.0f), glm::vec2()
		}
		,waiting_stand
	},
	{
		{
			glm::vec2(1.0f, 2.0f), glm::vec2()
		}
		,artillerie_stand
	}
};