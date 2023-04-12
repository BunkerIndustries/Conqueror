#include "_Game.h"
#include "Medic.h"

#include "scenes/GameScene/GameScene.h"

#include "required/constants.h"

void Medic::AddBuilding(Transform transform, uint32_t medicCount)
{
	GameObject* medicBuilding = gameScene->mapLayer->CreateBuilding(transform, "medic");
	medicBuilding->AddComponent(new MedicBuilding(medicCount));
}

void Medic::SendMedic()
{
	std::vector<GameObject*> medicBuildings = gameScene->mapLayer->GetGameObjectsByTag("medic_building");
	GameObject* nearestBuilding = nullptr;
	for (GameObject* medicBuilding : medicBuildings)
	{
		if (nearestBuilding == nullptr)
		{
			nearestBuilding = medicBuilding;
			continue;
		}
	}
	
	GameObject* medic = gameScene->allyLayer->CreateCharacter("medic", Transform(nearestBuilding->transform.position, character_scale, 0.0f));
	medic->AddComponent(new MedicCharacter(nearestBuilding));
	medic->GetComponent<Movement>()->target_position = &gameScene->GetActiveCharacter()->transform.position;
	nearestBuilding->GetComponent<MedicBuilding>()->SendMedic();
}

void Medic::ReturnMedic(GameObject* gameObject)
{
}
