#pragma once
#include "_Game.h"
#include "required/constants.h"


struct Stand {
	std::vector<GameObject*>* stand;
	uint8_t* choose_probability;
	uint8_t* hit_probability;
	glm::vec4* color;
};

inline Stand front_stand = { new std::vector<GameObject*>(), &front_choose_probability, &front_hit_probability, &node_front_color};
inline Stand mg_stand = { new std::vector<GameObject*>(), &mg_choose_probability, &mg_hit_probability, &node_mg_color };
inline Stand trench_stand = { new std::vector<GameObject*>(), &trench_choose_probability, &trench_hit_probability, &node_trench_color };
inline Stand hiding_stand = { new std::vector<GameObject*>(), &hiding_choose_probability, &hiding_hit_probability, &node_hiding_color };
inline Stand artillerie_stand = { new std::vector<GameObject*>(), &artillerie_choose_probability, &artillerie_hit_probability, &node_artillerie_color };

inline Stand bunker_stand = { new std::vector<GameObject*>(), nullptr, nullptr, &node_bunker_color };
inline Stand waiting_stand = { new std::vector<GameObject*>(), nullptr, nullptr, &node_waiting_color };

inline std::vector<Stand> shootable_stands = {
	front_stand, mg_stand, trench_stand, hiding_stand, artillerie_stand
};

inline std::array<std::array<GameObject*, enemy_grid_x>, enemy_grid_y> enemy_stands;
inline std::vector<GameObject*> waiting_nodes;
inline std::vector<GameObject*> trench_nodes;
inline std::vector<GameObject*> hiding_nodes;