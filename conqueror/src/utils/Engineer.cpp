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

}

bool Engineer::CheckForValidMGNodes() {
	for (auto node : *trench_stand.stand) {
		if (!node->GetComponent<Node>()->is_occupied) return true;
	}
	return false;
}

bool Engineer::CheckForValidArtillerieNodes() {

}