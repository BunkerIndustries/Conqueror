#pragma once
#include "_Game.h"

class GameScene;

class Medic
{
public:
	static GameObject* AddBuilding(Transform transform, uint32_t medicCount);
	static void SendMedic();
	static void ReturnMedic();
};

