#pragma once
#include "_Game.h"
#include 

class Util
{
public:
	static int RadToDeg(float rad);
	static int VectorAngle(float x, float y);

	static std::unordered_map<GameObject*, std::vector<SoldierShooting*>>;
};

