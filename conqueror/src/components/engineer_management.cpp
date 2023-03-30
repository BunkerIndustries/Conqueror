#include "_Game.h"
#include "engineer_management.h"
#include "required/constants.h"
#include "components/engineer_behaviour.h"
#include "components/movement.h"
#include "components/health.h"
#include "components/UI/character_ui.h"

EngineerManagement::EngineerManagement(uint8_t number_of_engineers)
	:available_engineers(number_of_engineers) 
{

}

void EngineerManagement::OnStart() {

}

void EngineerManagement::OnStop() {

}

void EngineerManagement::OnUpdate() {

}

void EngineerManagement::SendEngineer(GameObject* building_node) {
	if (available_engineers <= 0) return;

	available_engineers--;

	GameObject* engineer = new GameObject("engineer", Transform(gameObject->transform.position, character_scale));
	engineer->AddComponent(new SpriteRenderer(glm::vec4(0.5f, 0.6f, 0.0f, 0.4f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
	engineer->AddComponent(new Movement(engineer_movement_speed));
	engineer->AddComponent(new Health(engineer_health));
	engineer->AddComponent(new CharacterUI());
	engineer->AddComponent(new EngineerBehaviour(building_node));

	//TODO: foreground_layer->AddGameObjectToLayer(engineer);

}

void EngineerManagement::EngineerArrived() {
	available_engineers++;
}