#include "_Game.h"
#include "character_ui.h"
#include "required/constants.h"
#include "components/UI/ui_constants.h"
#include "components/health.h"
#include "components/soldier_behaviour.h"

CharacterUI::CharacterUI() {

}

void CharacterUI::OnStart() {

}

void CharacterUI::OnStop() {

}

void CharacterUI::OnUpdate() {

}

void CharacterUI::ToggleUI() {
	if (ui_toggled) {
		DeleteUI(); 
		ui_toggled = false;
		return;
	}
		
	CreateBackground();
	CreateHeader();
	if (gameObject->HasTag("soldier")) {
		CreateButtons();
	}

	for (auto& ui_element : ui_elements) {
		foreground_layer->AddGameObjectToLayer(ui_element);
	}
	ui_toggled = true;
}

void CharacterUI::CreateBackground() {
	glm::vec2 background_position = glm::vec2(
		1.0f - ui_background_size.x / 2.0f - screen_right_padding,
		0.0f);
	GameObject* background = new GameObject("ui_background", Transform(background_position, ui_background_size), ProjectionMode::SCREEN);
	background->AddComponent(new SpriteRenderer(ui_background_color, Geometry::RECTANGLE));
	ui_elements.push_back(background);
}

void CharacterUI::CreateHeader() {
	glm::vec2 header_placeholder_position = glm::vec2(
		ui_elements.at(0)->transform.position.x,
		ui_elements.at(0)->transform.position.y + (ui_elements.at(0)->transform.scale.y / 2.0f) - header_placeholder_height / 2.0f - ui_background_padding);
	
	glm::vec2 header_placeholder_scale = glm::vec2(
		ui_elements.at(0)->transform.scale.x - 2.0f * ui_background_padding,
		header_placeholder_height);

	GameObject* header_placeholder = new GameObject("header_placeholder", Transform(header_placeholder_position, header_placeholder_scale), ProjectionMode::SCREEN);
	header_placeholder->AddComponent(new SpriteRenderer(header_placeholder_color, Geometry::RECTANGLE));
	ui_elements.push_back(header_placeholder);
}

void CharacterUI::CreateButtons() {
	glm::vec2 call_medic_button_position = glm::vec2(
		ui_elements.at(0)->transform.position.x,
		ui_elements.at(1)->transform.position.y - ui_elements.at(1)->transform.scale.y / 2.0f - ui_elements_margin - button_height / 2.0f);
	
	glm::vec2 call_medic_button_scale = glm::vec2(
		ui_elements.at(0)->transform.scale.x * button_length_from_background - 2.0f * ui_background_padding,
		button_height);

	GameObject* call_medic_button = new GameObject("call_medic_button", Transform(call_medic_button_position, call_medic_button_scale), ProjectionMode::SCREEN);
	call_medic_button->AddComponent(new SpriteRenderer(call_medic_button_color, Geometry::RECTANGLE));
	call_medic_button->AddTag("call_medic_button");
	ui_elements.push_back(call_medic_button);
}

void CharacterUI::DeleteUI() {
	for (auto& ui_element : ui_elements) {
		delete ui_element;
	}
	ui_elements.clear();
	ui_toggled = false;
}

bool CharacterUI::UIElementPressed(GameObjectPressedEvent& e) {

	//LOG_DEBUG("UIElementPressed()");

	if (!(gameObject->HasTag("soldier") || gameObject->HasTag("medic") || gameObject->HasTag("engineer"))) return false;
	// show all stats of the character
	//LOG_DEBUG("character which ui was clicked is a character");

	if (!e.GetGameObject()->HasTag("call_medic_button") || (gameObject->HasTag("soldier") && gameObject->GetComponent<Health>()->GetHp() == soldier_health) || gameObject->GetComponent<SoldierBehaviour>()->is_healed) return false;	// if the clicked button is not call_medic_button or the soldier is full health
	medic_management->SendMedic(gameObject);
	gameObject->GetComponent<SoldierBehaviour>()->is_healed = true;
	//LOG_DEBUG("call medic");
	return true;
}