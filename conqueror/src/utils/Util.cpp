#include "_Game.h"
#include "Util.h"

#include <corecrt_math_defines.h>
std::unordered_map<GameObject*, std::vector<SoldierShooting*>> Util::soldierTable;
std::unordered_map<GameObject*, std::vector<EnemyShooting*>> Util::enemyTable;

int Util::RadToDeg(float rad)
{
	return rad * (180 / M_PI);
}

int Util::VectorAngle(float x, float y)
{
	if (x == 0) // special cases
		return (y > 0) ? 90
		: (y == 0) ? 0
		: 270;
	else if (y == 0) // special cases
		return (x >= 0) ? 0
		: 180;
	int ret = RadToDeg(atan2(y, x));
	if (x < 0 && y < 0) // quadrant Ⅲ
		ret = 180 + ret;
	else if (x < 0) // quadrant Ⅱ
		ret = 180 + ret; // it actually substracts
	else if (y < 0) // quadrant Ⅳ
		ret = 270 + (90 + ret); // it actually substracts
	return -ret;
}