#pragma once
#include "_Game.h"

class GameScene;

class Engineer
{
public:
	static void Init(GameScene* scene);

	static void AddBuilding(Transform transform, uint32_t engineerCount);
	static void SendEngineer(GameObject* gameObject);
	static void ReturnEngineer(GameObject* gameObject);

private:
	static GameScene* gameScene;
};

