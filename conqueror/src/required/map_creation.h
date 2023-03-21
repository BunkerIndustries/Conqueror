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
			glm::vec2(-7.0f, -8.0f),
			glm::vec2(-6.0f, -8.0f),
			glm::vec2(-7.0f, -7.0f),
			glm::vec2(-6.0f, -7.0f)
		}
		,waiting_stand
	},
	{
		{
			glm::vec2(8.0f, -4.0f),
			glm::vec2(7.0f, -4.0f),
			glm::vec2(6.0f, -3.75f),
			glm::vec2(5.0f, -3.5f),
			glm::vec2(2.0f, -3.0f),
			glm::vec2(1.0f, -3.0f),
			glm::vec2(0.0f, -3.0f),
			glm::vec2(-1.0f, -3.0f),
			glm::vec2(-2.0f, -3.0f),
			glm::vec2(-5.0f, -3.5f),
			glm::vec2(-6.0f, -3.75f),
			glm::vec2(-7.0f, -4.0f),
			glm::vec2( - 8.0f, -4.0f),
		}
		,trench_stand
	},
	{
		{
			glm::vec2(-4.0f, -3.0f),
			glm::vec2(-4.0f, -3.75f),
			glm::vec2(-3.0f, -3.75f),
			glm::vec2(-3.0f, -3.0f),


			glm::vec2(4.0f, -3.0f),
			glm::vec2(4.0f, -3.75f),
			glm::vec2(3.0f, -3.75f),
			glm::vec2(3.0f, -3.0f),
		}
		,bunker_stand
	},
	{
		{
			glm::vec2(-2.0f, -4.75f),
			glm::vec2(-6.0f, -5.5f),
			glm::vec2(6.0f, -5.5f),
			glm::vec2(2.0f, -4.75f),
			glm::vec2(0.0f, -5.5f)
		}
		,hiding_stand
	}
};