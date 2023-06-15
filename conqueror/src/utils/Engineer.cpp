#include "_Game.h"
#include "Engineer.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"
#include "required/stands.h"

Shr<Sound> Engineer::click;

void Engineer::Init()
{
	click = MakeShr<Sound>();

	click->LoadSound("assets/sounds/click.wav");
}

GameObject* Engineer::AddBuilding(Transform transform, uint32_t engineerCount)
{
	GameObject* engineerBuilding = layer->CreateBuilding(transform, "engineer");
	engineerBuilding->AddComponent(new EngineerBuilding(engineerCount));
	return engineerBuilding;
}

void Engineer::PlaceMG() {
	click->SoundPlay();
	if (gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->GetMgStock() <= 0) return;

	bool nop = true;
	for (size_t i = 0; i < trench_nodes.size(); i++) {
		if (!trench_nodes.at(i)->GetComponent<Node>()->is_occupied) {
			nop = false; 
			break;
		}
	}
	if (nop) return;

	gameScene->allyLayer->CreateEngineer(gameScene->mapLayer->engineerBuilding->transform.position, true);
	gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->DecreaseMgStock();
	gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->SendEngineer();
}

void Engineer::PlaceArtillerie() {
	click->SoundPlay();
	if (gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->GetArtilleryStock() <= 0) return;

	bool nop = true;
	for (size_t i = 0; i < hiding_nodes.size(); i++) {
		if (!hiding_nodes.at(i)->GetComponent<Node>()->is_occupied) {
			nop = false;
			break;
		}
	}
	if (nop) return;

	gameScene->allyLayer->CreateEngineer(gameScene->mapLayer->engineerBuilding->transform.position, false);
	gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->DecreaseArtilleryStock();
	gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->SendEngineer();
}