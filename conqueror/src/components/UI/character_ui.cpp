#include "character_ui.h"
#include "required/constants.h"


CharacterUI::CharacterUI() {

}

void CharacterUI::start() {

}

void CharacterUI::stop() {

}

void CharacterUI::update(float dt) {

}

void CharacterUI::ToggleUI() {
	if (ui_toggled) {
		LOG_DEBUG("return");
		DeleteUI(); 
		return;
	}
		
	
	this->CreateBackground();

	LOG_DEBUG("ui_elements.size() = {0}", ui_elements.size());
	for (auto& ui_element : ui_elements) {
		foreground_layer->AddGameObjectToLayer(ui_element);
	}
	ui_toggled = !ui_toggled;
}

void CharacterUI::CreateBackground() {
	LOG_DEBUG("CreateBackground()");
	GameObject* background = new GameObject("ui_background", Transform(ui_position, glm::vec2(1.0f, 1.0f)), ProjectionMode::SCREEN);
	background->AddComponent(new SpriteRenderer(ui_background_color));
	ui_elements.push_back(background);
}

void CharacterUI::DeleteUI() {
	LOG_DEBUG("DeleteUI()");
}

bool CharacterUI::UIElementPressed(GameObjectPressedEvent& e) {

	return false;
}