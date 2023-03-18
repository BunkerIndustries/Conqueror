#include "character_ui.h"
#include "required/constants.h"
#include "components/UI/ui_constants.h"

CharacterUI::CharacterUI() {

}

void CharacterUI::start() {

}

void CharacterUI::stop() {

}

void CharacterUI::update(float dt) {

}

void CharacterUI::ToggleUI() {
	LOG_DEBUG("ui_elements.size() = {0}", ui_elements.size());
	if (ui_toggled) {
		DeleteUI(); 
		ui_toggled = false;
		return;
	}
		
	CreateBackground();
	CreateHeader();

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
	background->AddComponent(new SpriteRenderer(ui_background_color));
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
	header_placeholder->AddComponent(new SpriteRenderer(header_placeholder_color));
	ui_elements.push_back(header_placeholder);
}

void CharacterUI::DeleteUI() {
	for (auto& ui_element : ui_elements) {
		ui_element->Delete();
	}
	ui_elements.clear();
	ui_toggled = false;
}

bool CharacterUI::UIElementPressed(GameObjectPressedEvent& e) {

	return false;
}