#include "medic_management.h"
#include "required/constants.h"
#include "required/functions.h"
#include "components/medic_behaviour.h"

MedicManagement::MedicManagement(uint8_t number_of_medics)
	:available_medics(number_of_medics)
{

}

void MedicManagement::start() {
	
}

void MedicManagement::stop() {

}

void MedicManagement::update(float dt) {

}

void MedicManagement::SendMedic(GameObject* healing_target) {
	if (available_medics <= 0) return;
	
	available_medics--;

	GameObject* medic = new GameObject("medic", Transform(gameObject->transform.position, character_scale));
	medic->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));		// TODO: Change to sprite_path
	medic->AddComponent(new Movement(medic_movement_speed));
	medic->AddComponent(new Health(medic_health));
	medic->AddComponent(new CharacterUI());
	medic->AddComponent(new MedicBehaviour(healing_target));

	foreground_layer->AddGameObjectToLayer(medic);

}

void MedicManagement::MedicArrived() {
	available_medics++;
}