#pragma once
#include "Engine.h"
#include "required/constants.h"
#include <vector>


inline std::vector<GameObject*> bunker_stand;
inline std::vector<GameObject*> waiting_stand;

struct Stand {
	std::vector<GameObject*>* stand;
	uint8_t* choose_probability;
	uint8_t* hit_probability;
};

inline Stand front_stand = { &std::vector<GameObject*>(), &front_choose_probability, &front_hit_probability };
inline Stand mg_stand = { &std::vector<GameObject*>(), &mg_choose_probability, &mg_hit_probability };
inline Stand trench_stand = { &std::vector<GameObject*>(), &trench_choose_probability, &trench_hit_probability };
inline Stand hiding_stand = { &std::vector<GameObject*>(), &hiding_choose_probability, &hiding_hit_probability };
inline Stand artillerie_stand = { &std::vector<GameObject*>(), &artillerie_choose_probability, &artillerie_hit_probability };

inline std::vector<Stand> shootable_stands = {
	front_stand, mg_stand, trench_stand, hiding_stand, artillerie_stand
};
