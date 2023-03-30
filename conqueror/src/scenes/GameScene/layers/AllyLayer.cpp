#include "_Game.h"

#include "AllyLayer.h"
#include "required/constants.h"

AllyLayer::AllyLayer()
	: Layer("AllyLayer")
{
	CreateCharacter("soldier", glm::vec2(-5.0f, -5.0f));
	CreateCharacter("soldier", glm::vec2(-4.0f, -5.0f));
	/*CreateCharacter("soldier", glm::vec2(2.0f, 1.0f));
	CreateCharacter("soldier", glm::vec2(2.5f, 1.0f));
	CreateCharacter("soldier", glm::vec2(3.0f, 1.0f));*/
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

}

GameObject* AllyLayer::CreateCharacter(std::string type, glm::vec2 spawn_pos) {
	float movement_speed = 0.0f;
	float health = 0.0f;
	std::string sprite_path;
	GameObject* character_go = new GameObject(type, Transform(spawn_pos, character_scale));

	// set paths and movement speeds regarding the type of the character
	if (type == "soldier") {

		movement_speed = soldier_movement_speed; sprite_path = soldier_sprite_path;
		health = soldier_health;

		character_go->AddComponent(new SoldierBehaviour());
		character_go->AddComponent(new SoldierShooting());

	}
	else if (type == "engineer") {
		movement_speed = engineer_movement_speed; sprite_path = engineer_sprite_path;
		health = engineer_health;
	}
	else LOG_WARN("WARNING: probably no existing type given when creating a character");

	character_go->AddTag(type);
	character_go->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
	character_go->AddComponent(new Movement(movement_speed));
	character_go->AddComponent(new Health(health));
	character_go->AddComponent(new CharacterUI());

	AddGameObjectToLayer(character_go);

	return character_go;
}