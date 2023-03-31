#include "_Game.h"
#include "Engineer.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"

void Engineer::AddBuilding(Transform transform, uint32_t engineerCount)
{
	GameObject* engineerBuilding = gameScene->mapLayer->CreateBuilding(transform, "engineer");
	engineerBuilding->AddComponent(new EngineerBuilding(engineerCount));
}

void Engineer::SendEngineer(GameObject* gameObject)
{
	//TODO: get function to get gameobjects from layer
	//if (available_engineers <= 0) return;
	//engineer->AddComponent(new EngineerBehaviour(building_node));

}

void Engineer::ReturnEngineer(GameObject* gameObject)
{
}
