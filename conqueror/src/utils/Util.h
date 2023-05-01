#pragma once
#include "_Game.h"

class Util
{
public:
	static int RadToDeg(float rad);
	static int VectorAngle(float x, float y);

	static std::unordered_map<GameObject*, std::vector<SoldierShooting*>> soldierTable;
	static std::unordered_map<GameObject*, std::vector<EnemyShooting*>> enemyTable;
};

