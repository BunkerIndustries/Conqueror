#include "_Game.h"
#include "Medic.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"

GameObject* Medic::AddBuilding(MapLayer* layer, Transform transform, uint32_t medicCount)
{
	GameObject* medicBuilding = layer->CreateBuilding(transform, "medic");
	medicBuilding->AddComponent(new MedicBuilding(medicCount));
	return medicBuilding;
}

void Medic::SendMedic()
{
	if (gameScene->GetActiveCharacter()->GetComponent<Health>()->GetHp() == soldier_health
		|| gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->ReceivingMedic()) {
		return;
	}
	gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->SendMedic();
}
