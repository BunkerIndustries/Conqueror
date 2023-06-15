#pragma once
#include "_Game.h"

class Util
{
public:
	static float RadToDeg(float rad);
	static float DegToRad(float deg);
	static int VectorAngle(glm::vec2 point);
	static glm::vec2 VectorAngle(float angle);

	static std::unordered_map<GameObject*, std::vector<SoldierShooting*>> soldierTable;
	static std::unordered_map<GameObject*, std::vector<EnemyShooting*>> enemyTable;
	static std::unordered_map<GameObject*, std::vector<MgComponent*>> mgTable;
	static std::unordered_map<GameObject*, std::vector<ArtilleryComponent*>> artillerieTable;

	static Shr<Sound> menu_select;

	static void Init();
};

