#pragma once
#include "_Game.h"

class GameScene;

class Medic
{
public:
	static void AddBuilding(Transform transform, uint32_t medicCount);
	static void SendMedic(GameObject* gameObject);
	static void ReturnMedic(GameObject* gameObject);
};

