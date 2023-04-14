#include "_Game.h"
#include "Engineer.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"
#include "required/stands.h"

GameObject* Engineer::AddBuilding(Transform transform, uint32_t engineerCount)
{
	GameObject* engineerBuilding = gameScene->mapLayer->CreateBuilding(transform, "engineer");
	engineerBuilding->AddComponent(new EngineerBuilding(engineerCount));
	return engineerBuilding;
}

void Engineer::PlaceMG() {
	bool nop = true;
	for (size_t i = 0; i < trench_stand.stand->size(); i++) {
		if (!trench_stand.stand->at(i)->GetComponent<Node>()->is_occupied) nop = false; break;
	}
	if (nop) return;

	gameScene->allyLayer->CreateEngineer(gameScene->mapLayer->engineerBuilding->transform.position, trench_stand);
}

void Engineer::PlaceArtillerie() {
	bool nop = true;
	for (size_t i = 0; i < trench_stand.stand->size(); i++) {
		if (!trench_stand.stand->at(i)->GetComponent<Node>()->is_occupied) nop = false; break;
	}
	if (nop) return;

	gameScene->allyLayer->CreateEngineer(gameScene->mapLayer->engineerBuilding->transform.position, hiding_stand);
}