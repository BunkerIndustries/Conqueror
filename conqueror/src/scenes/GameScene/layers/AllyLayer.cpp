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

Shr<Sound> AllyLayer::soldier_click;
Shr<Sound> AllyLayer::engineer_click;
Shr<Sound> AllyLayer::medic_click;

void AllyLayer::Init()
{
	soldier_click = MakeShr<Sound>();
	engineer_click = MakeShr<Sound>();
	medic_click = MakeShr<Sound>();

	soldier_click->LoadSound("assets/sounds/soldier_click.wav");
	engineer_click->LoadSound("assets/sounds/engineer_click.wav");
	medic_click->LoadSound("assets/sounds/medic_click.wav");
}

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
	Supply::TryCallSoldier();
}

GameObject* AllyLayer::CreateSoldier(glm::vec2 position) {
	GameObject* character = new GameObject("soldier", Transform(position, character_scale));
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Anims/Soldier/German_Soldier_MG_fixed-0001.png"), 200.0f, 304.0f, 16.0f, 16.0f, glm::vec2(0, 0)));
	character->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(3, 0));
	character->AddComponent(new Movement(soldier_movement_speed));
	character->AddComponent(new Health(soldier_health));
	character->AddComponent(new SoldierBehaviour());
	character->AddComponent(new SoldierShooting());
	character->AddComponent(new WalkingAnimation(glm::vec2(3.0f, 1.0f), glm::vec2(5.0f, 1.0f), glm::vec2(3.0f, 0.0f), glm::vec2(5.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), 0.5f, glm::vec2(3.0f, 1.0f), false));
	character->AddTag("soldier");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateMedic(glm::vec2 position) {
	GameObject* character = new GameObject("medic", Transform(position, medic_size));
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Anims/Med/med_walk_fixed-0001.png"), 112.0f, 304.0f, 24.0f, 16.0f, glm::vec2(0, 0)));
	character->AddComponent(new Movement(medic_movement_speed));
	character->AddComponent(new Health(medic_health));
	character->AddComponent(new MedicCharacter(gameScene->mapLayer->medicBuilding));
	character->AddComponent(new WalkingAnimation(glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(3.0f, 0.0f), glm::vec2(5.0f, 0.0f), glm::vec2(3.0f, 1.0f), glm::vec2(5.0f, 1.0f), 0.5f, glm::vec2(0.0f, 1.0f), false));
	character->AddTag("medic");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
}

GameObject* AllyLayer::CreateEngineer(glm::vec2 position, bool mg_artillery) {
	GameObject* character = new GameObject("engineer", Transform(position, engineer_scale));
	character->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Anims/Engineer/engineer_walk_sideways.png"), 112.0f, 304.0f, 24.0f, 16.0f, glm::vec2(0, 0)));
	character->AddComponent(new Movement(engineer_movement_speed));
	character->AddComponent(new Health(engineer_health));
	character->AddComponent(new EngineerCharacter(mg_artillery));
	character->AddComponent(new WalkingAnimation(glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 1.0f), 0.5f, glm::vec2(0.0f, 1.0f), true));
	character->AddComponent(new SingleAnimation(DataPool::GetTexture("Anims/Engineer/engineer_build_animation_fixedsprite.png"), 176.0f, 304.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 0.0f), 10, glm::vec2(0.0f, 1.0f), DataPool::GetTexture("Anims/Engineer/engineer_walk_sideways.png"), 112.0f, 304.0f, 24.0f, 16.0f));
	character->AddTag("engineer");
	character->onlyLayerReceive = true;
	AddGameObjectToLayer(character);
	return character;
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

	if (clicked_character->HasTag("soldier") && !clicked_character->GetComponent<SoldierBehaviour>()->on_spawn_pos) {
		gameScene->SetActiveCharacter(clicked_character);
		gameScene->uiLayer->DeactivateCharacterUI();
		gameScene->uiLayer->ActivateSoldierUI();
		soldier_click->SoundPlay();
	}
	else if (clicked_character->HasTag("medic")) {
		gameScene->SetActiveCharacter(clicked_character);
		gameScene->uiLayer->DeactivateCharacterUI();
		gameScene->uiLayer->ActivateMedicUI();
		medic_click->SoundPlay();
	}
	else if (clicked_character->HasTag("engineer")) {
		gameScene->SetActiveCharacter(clicked_character);
		gameScene->uiLayer->DeactivateCharacterUI();
		gameScene->uiLayer->ActivateEngineerUI();
		engineer_click->SoundPlay();
	}
	else {
		return false;
	}

	return true;
}