#include "_Game.h"
#include "building_ui.h"
#include "required/constants.h"

BuildingUI::BuildingUI() {

}

void BuildingUI::OnStart() {

}

void BuildingUI::OnStop() {

}

void BuildingUI::OnUpdate() {

}

void BuildingUI::OpenUI() {

	CreateBackground();
	CreateHeader();
	if (gameObject->HasTag("engineer_building")) {
		CreateButtons();
	}

	for (auto& ui_element : building_ui_elements) {
		gameScene->uiLayer->AddGameObjectToLayer(ui_element);
	}
}

void BuildingUI::CreateBackground() {
	glm::vec2 background_position = glm::vec2(
		-1.0f + ui_background_size.x / 2.0f + screen_padding,
		0.0f);
	GameObject* background = new GameObject("ui_background", Transform(background_position, ui_background_size), ProjectionMode::SCREEN);
	background->AddComponent(new SpriteRenderer(ui_background_color, Geometry::RECTANGLE));
	building_ui_elements.push_back(background);
}

void BuildingUI::CreateHeader() {
	glm::vec2 header_placeholder_position = glm::vec2(
		building_ui_elements.at(0)->transform.position.x,
		building_ui_elements.at(0)->transform.position.y + (building_ui_elements.at(0)->transform.scale.y / 2.0f) - header_placeholder_height / 2.0f - ui_background_padding);

	glm::vec2 header_placeholder_scale = glm::vec2(
		building_ui_elements.at(0)->transform.scale.x - 2.0f * ui_background_padding,
		header_placeholder_height);

	GameObject* header_placeholder = new GameObject("header_placeholder", Transform(header_placeholder_position, header_placeholder_scale), ProjectionMode::SCREEN);
	header_placeholder->AddComponent(new SpriteRenderer(header_placeholder_color, Geometry::RECTANGLE));
	building_ui_elements.push_back(header_placeholder);
}

void BuildingUI::CreateButtons() {
	glm::vec2 button_position = glm::vec2(
		building_ui_elements.at(0)->transform.position.x,
		building_ui_elements.at(1)->transform.position.y - building_ui_elements.at(1)->transform.scale.y / 2.0f - ui_elements_margin - button_height / 2.0f);

	glm::vec2 button_scale = glm::vec2(
		building_ui_elements.at(0)->transform.scale.x * button_length_from_background - 2.0f * ui_background_padding,
		button_height);

	GameObject* button = new GameObject("send_engineer_button", Transform(button_position, button_scale), ProjectionMode::SCREEN);
	button->AddTag("send_engineer_button");
	button->AddComponent(new SpriteRenderer(send_engineer_button_color, Geometry::RECTANGLE));
	building_ui_elements.push_back(button);
}

void BuildingUI::DeleteUI() {
	for (auto& ui_element : building_ui_elements) {
		delete ui_element;
	}
	building_ui_elements.clear();
}

bool BuildingUI::UIElementPressed(GameObjectPressedEvent& e) {


	if (!e.GetGameObject()->HasTag("send_engineer_button")) return false;
	// show all stats
	LOG_DEBUG("has tag medic_building or engineer_building");


	return true;
}