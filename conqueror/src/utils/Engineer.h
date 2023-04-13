#pragma once
#include "_Game.h"

class GameScene;

class Engineer
{
public:
	static GameObject* AddBuilding(Transform transform, uint32_t engineerCount);
	static void PlaceMG();
	static bool CheckForValidArtillerieNodes();
};

