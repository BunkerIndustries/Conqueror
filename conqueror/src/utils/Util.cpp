#include "_Game.h"
#include "Util.h"

#include <corecrt_math_defines.h>
std::unordered_map<GameObject*, std::vector<SoldierShooting*>> Util::soldierTable;
std::unordered_map<GameObject*, std::vector<EnemyShooting*>> Util::enemyTable;
std::unordered_map<GameObject*, std::vector<MgComponent*>> Util::mgTable;
std::unordered_map<GameObject*, std::vector<ArtilleryComponent*>> Util::artillerieTable;

Shr<Sound> Util::menu_select;

void Util::Init()
{
	menu_select = MakeShr<Sound>();
	menu_select->LoadSound("assets/sounds/start.wav");
}

float Util::RadToDeg(float rad)
{
	return rad * (180 / M_PI);
}

float Util::DegToRad(float deg)
{
	return deg * (M_PI / 180);
}

int Util::VectorAngle(glm::vec2 point)
{
	if (point.x == 0) // special cases
		return (point.y > 0) ? 90
		: (point.y == 0) ? 0
		: 270;
	else if (point.y == 0) // special cases
		return (point.x >= 0) ? 0
		: 180;
	int ret = RadToDeg(atan2(point.y, point.x));
	return ret;
	if (point.x < 0 && point.y < 0) // quadrant Ⅲ
		ret = 180 + ret;
	else if (point.x < 0) // quadrant Ⅱ
		ret = 180 + ret; // it actually substracts
	else if (point.y < 0) // quadrant Ⅳ
		ret = 270 + (90 + ret); // it actually substracts
	return -ret;
}

glm::vec2 Util::VectorAngle(const float angle)
{
	const float rad = glm::radians(angle);
	glm::vec2 pos;
	pos.x = glm::cos(rad);
	pos.y = glm::sin(rad);
	return pos;
}