#include "_Game.h"

#include "AllyLayer.h"
#include "required/constants.h"
#include "utils/SoldierSupply.h"
#include "components/MgComponent.h"

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

void AllyLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) 
	{
		if (e.getKeyCode() == KEY_SPACE) {
			SoldierSupply::TryCallSoldier();
			return true;
		}
		return false;
	});
}

GameObject* AllyLayer::CreateCharacter(std::string type, Transform transform) {
	GameObject* character = new GameObject(type, transform);
	character->AddTag(type);

	// set paths and movement speeds regarding the type of the character
	if (type == "soldier") {

		character->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
		character->AddComponent(new Movement(soldier_movement_speed));
		character->AddComponent(new Health(soldier_health));
		character->AddComponent(new CharacterUI());
		character->AddComponent(new SoldierBehaviour());
		character->AddComponent(new SoldierShooting());

	}
	else if (type == "engineer") {
		character->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.6f, 0.0f, 0.4f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
		character->AddComponent(new Movement(engineer_movement_speed));
		character->AddComponent(new Health(engineer_health));
		character->AddComponent(new CharacterUI());
	}
	else if(type == "medic")
	{ 
		character->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.5f, 0.0f, 0.8f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
		character->AddComponent(new Movement(medic_movement_speed));
		character->AddComponent(new Health(medic_health));
		character->AddComponent(new CharacterUI());
	}
	else LOG_WARN("WARNING: probably no existing type given when creating a character");

	AddGameObjectToLayer(character);

	return character;
}

GameObject* AllyLayer::CreateMg(glm::vec2 mg_node_position) {

	GameObject* mg = new GameObject("mg", Transform(mg_node_position,mg_size));
	mg->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.1f, 0.5f, 1.0f), Geometry::RECTANGLE));
	mg->AddComponent(new MgComponent());
	AddGameObjectToLayer(mg);

	return mg;
}