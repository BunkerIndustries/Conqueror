#pragma once
#include "_Game.h"

class GameScene;

class Engineer
{
public:
	static GameObject* AddBuilding(MapLayer* layer, Transform transform, uint32_t engineerCount);
	static void PlaceMG();
	static void PlaceArtillerie();

	static void Init();

	static Shr<Sound> click;
};

