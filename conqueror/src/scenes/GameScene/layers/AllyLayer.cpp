#include "_Game.h"

#include "AllyLayer.h"
#include "required/constants.h"
#include "utils/Supply.h"
#include "components/MgComponent.h"
#include "components/ArtilleryComponent.h"
#include "scenes/GameScene/GameScene.h"
#include "required/stands.h"
#include "components/WalkingAnimationComponent.h"
#include "components/SingleAnimationComponent.h"


AllyLayer::AllyLayer()
	: Layer("AllyLayer")
{
	

}

AllyLayer::~AllyLayer()
{
	
}

void AllyLayer::OnAttach()
{

}

void AllyLayer::OnDetach()
{

}

void AllyLayer::Update(const float dt)
{

}

GameObject* AllyLayer::CreateSoldier(glm::vec2 position) {
	GameObject* character = new GameObject("soldier", Transform(position, character_scale));
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("/Anims/Soldier/German_Soldier_MG-0001.png"), 200.0f, 304.0f, 16.0f, 16.0f, glm::vec2(0, 0)));
	character->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(3, 0));
	character->AddComponent(new Movement(soldier_movement_speed));
	character->AddComponent(new Health(soldier_health));
	character->AddComponent(new SoldierBehaviour());
	character->AddComponent(new SoldierShooting());
	character->AddComponent(new WalkingAnimation(glm::vec2(3.0f, 1.0f), glm::vec2(5.0f, 1.0f), glm::vec2(3.0f, 0.0f), glm::vec2(5.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), 10, glm::vec2(3.0f, 1.0f), false));
	character->AddTag("soldier");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateMedic(glm::vec2 position) {
	GameObject* character = new GameObject("medic", Transform(position, character_scale));
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Anims/Engineer/med_walk_fixed-0001.png"), 112.0f, 304.0f, 24.0f, 16.0f, glm::vec2(0, 0)));
	character->AddComponent(new Movement(medic_movement_speed));
	character->AddComponent(new Health(medic_health));
	character->AddComponent(new MedicCharacter(gameScene->mapLayer->medicBuilding));
	character->AddComponent(new WalkingAnimation(glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(3.0f, 0.0f), glm::vec2(5.0f, 0.0f), glm::vec2(3.0f, 1.0f), glm::vec2(5.0f, 1.0f), 16, glm::vec2(0.0f, 1.0f), false));
	character->AddTag("medic");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateEngineer(glm::vec2 position, bool mg_artillery) {
	GameObject* character = new GameObject("engineer", Transform(position, character_scale));
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Anims/Engineer/engineer_walk_sideways.png"), 112.0f, 304.0f, 24.0f, 16.0f, glm::vec2(0, 0)));
	character->AddComponent(new Movement(engineer_movement_speed));
	character->AddComponent(new Health(engineer_health));
	character->AddComponent(new EngineerCharacter(mg_artillery));
	character->AddComponent(new WalkingAnimation(glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), 10, glm::vec2(0.0f, 1.0f), true));
	character->AddComponent(new SingleAnimation(DataPool::GetTexture("Anims/Engineer/engineer_build.png"), 168.0f, 304.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 3.0f), 10, glm::vec2(0.0f, 1.0f), DataPool::GetTexture("Anims/Engineer/engineer_walk_sideways.png"), 112.0f, 304.0f, 16.0f, 16.0f));
	character->AddTag("engineer");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateMg(glm::vec2 mg_position, GameObject* mg_node) {

	GameObject* mg = new GameObject("mg", Transform(mg_position,mg_size));
	mg->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.1f, 0.5f, 1.0f), Geometry::RECTANGLE));
	mg->AddComponent(new MgComponent(mg_node));
	AddGameObjectToLayer(mg);

	return mg;
}

GameObject* AllyLayer::CreateArtillery(glm::vec2 artillery_position, GameObject* artillery_node) {

	GameObject* artillery = new GameObject("artillery", Transform(artillery_position, artillery_size));
	artillery->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.1f, 0.5f, 1.0f), Geometry::RECTANGLE));
	artillery->AddComponent(new ArtilleryComponent(artillery_node));
	AddGameObjectToLayer(artillery);

	return artillery;
}

bool AllyLayer::KeyReleased(KeyReleasedEvent& e) {
	if (e.getKeyCode() == KEY_SPACE) {
		Supply::TryCallSoldier();
		return true;
	}
	return false;
}

bool AllyLayer::GameObjectPressed(GameObjectPressedEvent& e) {
	// check if e belongs to allylayer - otherwise return false

	GameObject* clicked_character = e.GetGameObject();

	if (clicked_character == gameScene->GetActiveCharacter()) {
		gameScene->uiLayer->DeactivateCharacterUI();
		gameScene->SetActiveCharacter(nullptr);
		return true;
	}
	else {
		gameScene->uiLayer->DeactivateCharacterUI();
	}

	if (clicked_character->HasTag("soldier") && !clicked_character->GetComponent<SoldierBehaviour>()->on_spawn_pos) {
		gameScene->uiLayer->ActivateSoldierUI();
	}
	else if (clicked_character->HasTag("medic")) {
		gameScene->uiLayer->ActivateMedicUI();
	}
	else if (clicked_character->HasTag("engineer")) {
		gameScene->uiLayer->ActivateEngineerUI();
	}
	else {
		return false;
	}

	gameScene->SetActiveCharacter(clicked_character);

	return true;
}