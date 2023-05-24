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
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Anims/Med/med_walk_fixed-0001.png"), 112.0f, 304.0f, 24.0f, 16.0f, glm::vec2(0, 0)));
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
	character->AddComponent(new SingleAnimation(DataPool::GetTexture("Anims/Engineer/engineer_build.png"), 168.0f, 304.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 0.0f), 10, glm::vec2(0.0f, 1.0f), DataPool::GetTexture("Anims/Engineer/engineer_walk_sideways.png"), 112.0f, 304.0f, 16.0f, 16.0f));
	character->AddTag("engineer");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateMg(glm::vec2 mg_position, GameObject* mg_node) {

	GameObject* mg = new GameObject("mg", Transform(mg_position,mg_size));
	mg->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Buildings/mg_animation.png"), 80.0f, 224.0f, 0.0f, 0.0f, glm::vec2(0, 0)));
	mg->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(0, 0));
	mg->AddComponent(new SingleAnimation(DataPool::GetTexture("Anims/mg_animation.png"), 104.0f, 296.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 0.0f), 10, glm::vec2(0.0f, 0.0f), DataPool::GetTexture("Anims/mg_animation.png"), 104.0f, 296.0f, 16.0f, 16.0f));
	mg->AddComponent(new MgComponent(mg_node));
	AddGameObjectToLayer(mg);

	return mg;
}

GameObject* AllyLayer::CreateArtillery(glm::vec2 artillery_position, GameObject* artillery_node) {

	GameObject* artillery = new GameObject("artillery", Transform(artillery_position, artillery_size));
	artillery->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Buildings/artillerie_front_north.png"), 248.0f, 400.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f)));
	artillery->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(0.0f, 0.0f));
	artillery->AddComponent(new ArtilleryComponent(artillery_node));

	artillery->AddComponent(new SingleAnimation(DataPool::GetTexture("Buildings/artillerie_front_north.png"), 248.0f, 400.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), artillery_shoot_anim_speed, glm::vec2(0.0f, 0.0f), DataPool::GetTexture("Buildings/artillerie_front_north.png"), 248.0f, 400.0f, 16.0f, 16.0f));

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
		gameScene->SetActiveCharacter(nullptr);
		gameScene->uiLayer->DeactivateCharacterUI();
		return true;
	}
	else {
		gameScene->uiLayer->DeactivateCharacterUI();
	}

	if (clicked_character->HasTag("soldier") && !clicked_character->GetComponent<SoldierBehaviour>()->on_spawn_pos) {
		gameScene->SetActiveCharacter(clicked_character);
		gameScene->uiLayer->ActivateSoldierUI();
	}
	else if (clicked_character->HasTag("medic")) {
		gameScene->SetActiveCharacter(clicked_character);
		gameScene->uiLayer->ActivateMedicUI();
	}
	else if (clicked_character->HasTag("engineer")) {
		gameScene->SetActiveCharacter(clicked_character);
		gameScene->uiLayer->ActivateEngineerUI();
	}
	else {
		return false;
	}

	return true;
}