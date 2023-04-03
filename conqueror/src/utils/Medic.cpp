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
	std::vector<GameObject*> medicBuildings = gameScene->mapLayer->GetGameObjectsByTag("medic_building");
	GameObject* nearestBuilding = nullptr;
	for (GameObject* medicBuilding : medicBuildings)
	{
		if (nearestBuilding == nullptr)
		{
			nearestBuilding = medicBuilding;
			continue;
		}

		//FIND NEAREST BUILDING WITH AVAILABLE MEDICS
		/*nearestBuilding->
		 * if (available_Medics <= 0) return;
		 *
		 */
	}
	//TODO: get function to get gameobjects from layer
	//
	//->AddComponent(new MedicCharacter(healing_target));
	GameObject* medic = gameScene->allyLayer->CreateCharacter("medic", Transform(nearestBuilding->transform.position, character_scale, 0.0f));
	medic->AddComponent(new MedicCharacter(nearestBuilding, gameObject));
	medic->GetComponent<Movement>()->target_position = &gameObject->transform.position;
	nearestBuilding->GetComponent<MedicBuilding>()->SendMedic();
}

void Medic::ReturnMedic(GameObject* gameObject)
{
}
