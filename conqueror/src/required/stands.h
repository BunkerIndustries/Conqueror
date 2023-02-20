#pragma once
#include "Engine.h"
#include "required/constants.h"
#include <vector>

// Any stands soldiers can be (They will change dynamically between them)
// inline could be removed at the current state

inline std::vector<GameObject*> bunker_stand;
inline std::vector<GameObject*> waiting_stand;

struct Stand{
	std::vector<GameObject*> stand;
	uint8_t* choose_probability;
	uint8_t* hit_probability;
};

Stand front_stand = { std::vector<GameObject*>(), &front_choose_probability, &front_hit_probability};
Stand mg_stand = { std::vector<GameObject*>(), &mg_choose_probability, &mg_hit_probability };
Stand trench_stand = { std::vector<GameObject*>(), &trench_choose_probability, &trench_hit_probability };
Stand hiding_stand = { std::vector<GameObject*>(), &hiding_choose_probability, &hiding_hit_probability };
Stand artillerie_stand = { std::vector<GameObject*>(), &artillerie_choose_probability, &artillerie_hit_probability }; 


// ZIEL: Bei LockTarget() soll ein random vektor ausgewählt werden (nach choose_wahrscheinlichkeiten) und bei Shoot gewusst werden welche hitwahrscheinlichkeit der stand hat
// PROBLEM: viel zu viele variablen, die von constants nochmal in die structs kopiert werden -> in den struct einen pointer machen auf den stand_vektor