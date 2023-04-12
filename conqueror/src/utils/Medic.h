#pragma once
#include "_Game.h"

class GameScene;

class Medic
{
public:
	static void AddBuilding(Transform transform, uint32_t medicCount);
	static void SendMedic();
	static void ReturnMedic(GameObject* gameObject);
};

