#include "_Game.h"
#include "Medic.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"

void Medic::AddBuilding(Transform transform, uint32_t medicCount)
{
	GameObject* medicBuilding = gameScene->mapLayer->CreateBuilding(transform, "medic");
	medicBuilding->AddComponent(new MedicBuilding(medicCount));
}

void Medic::SendMedic(GameObject* gameObject)
{
	//TODO: get function to get gameobjects from layer
	//if (available_Medics <= 0) return;
	//->AddComponent(new MedicCharacter(healing_target));


}

void Medic::ReturnMedic(GameObject* gameObject)
{
}
