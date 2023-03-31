#include "_Game.h"

#include "AllyLayer.h"
#include "required/constants.h"

AllyLayer::AllyLayer()
	: Layer("AllyLayer")
{
	

}

AllyLayer::~AllyLayer()
{
	
}

void AllyLayer::OnAttach()
{
	CreateCharacter("soldier", glm::vec2(-5.0f, -5.0f));
	CreateCharacter("soldier", glm::vec2(-4.0f, -5.0f));
	/*CreateCharacter("soldier", glm::vec2(2.0f, 1.0f));
	CreateCharacter("soldier", glm::vec2(2.5f, 1.0f));
	CreateCharacter("soldier", glm::vec2(3.0f, 1.0f));*/
}

void AllyLayer::OnDetach()
{

}

void AllyLayer::Update(const float dt)
{

}

void AllyLayer::OnEvent(Event& event)
{

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
	else LOG_WARN("WARNING: probably no existing type given when creating a character");

	AddGameObjectToLayer(character);

	return character;
}