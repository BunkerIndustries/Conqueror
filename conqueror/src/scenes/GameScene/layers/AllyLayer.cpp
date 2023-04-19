#include "_Game.h"

#include "AllyLayer.h"
#include "required/constants.h"
#include "utils/Supply.h"
#include "components/MgComponent.h"
#include "scenes/GameScene/GameScene.h"
#include "required/stands.h"


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
	character->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
	character->AddComponent(new Movement(soldier_movement_speed));
	character->AddComponent(new Health(soldier_health));
	character->AddComponent(new SoldierBehaviour());
	character->AddComponent(new SoldierShooting());
	character->AddTag("soldier");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateMedic(glm::vec2 position) {
	GameObject* character = new GameObject("medic", Transform(position, character_scale));
	character->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.5f, 0.0f, 0.8f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
	character->AddComponent(new Movement(medic_movement_speed));
	character->AddComponent(new Health(medic_health));
	character->AddComponent(new MedicCharacter(gameScene->mapLayer->medicBuilding));
	character->AddTag("medic");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateEngineer(glm::vec2 position, Stand stand) {
	GameObject* character = new GameObject("engineer", Transform(position, character_scale));
	character->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.6f, 0.0f, 0.4f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
	character->AddComponent(new Movement(engineer_movement_speed));
	character->AddComponent(new Health(engineer_health));
	character->AddComponent(new EngineerCharacter(stand));
	character->AddTag("engineer");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateMg(glm::vec2 mg_position) {

	GameObject* mg = new GameObject("mg", Transform(mg_position,mg_size));
	mg->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.1f, 0.5f, 1.0f), Geometry::RECTANGLE));
	mg->AddComponent(new MgComponent());
	AddGameObjectToLayer(mg);

	return mg;
}

GameObject* AllyLayer::CreateArtillery(glm::vec2 artillery_position) {

	GameObject* artillery = new GameObject("artillery", Transform(artillery_position, mg_size));
	artillery->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.1f, 0.5f, 1.0f), Geometry::RECTANGLE));
	artillery->AddComponent();
	AddGameObjectToLayer(artillery);

	return mg;
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