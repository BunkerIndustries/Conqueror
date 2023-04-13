#include "_Game.h"

#include "UILayer.h"

#include "required/constants.h"
#include "scenes/GameScene/GameScene.h"
#include "utils/Medic.h"
#include "utils/Engineer.h"

UILayer::UILayer()
	: Layer("UILayer")
{
}

UILayer::~UILayer()
{
}

void UILayer::OnAttach()
{
}

void UILayer::OnDetach()
{
}

void UILayer::Update(const float dt)
{
}


void UILayer::ActivateSoldierUI() {
	character_background = new Panel(ui_character_background_color, Transform(glm::vec2(0.0f, 0.85f), ui_background_size), Type::Rectangle, "ui_character_background");

	Panel* header = new Panel(ui_header_color, Transform(glm::vec2(0.0f, 0.7f), glm::vec2(0.9f, 0.2f)), Type::Rectangle, "ui_character_header");
	// picturebox with picture of soldier
	Label* name = new Label("Soldier: ", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.2f, 0.0f), glm::vec2(0.8f, 0.2f)), "ui_character_name");
	Button* call_medic_button = new Button(ui_call_medic_button_color, Transform(glm::vec2(0.0f, 0.5f), glm::vec2(0.8f, 0.2f)), Type::Rectangle, Medic::SendMedic, "ui_call_medic_button");
	// add picturebox child object
	header->AddChildObject(name); 
	header->AddChildObject(call_medic_button);

	character_background->AddChildObject(header);
}

void UILayer::ActivateMedicUI() {
	character_background = new Panel(ui_character_background_color, Transform(glm::vec2(0.0f, 0.85f), ui_background_size), Type::Rectangle, "ui_character_background");

	Panel* header = new Panel(ui_header_color, Transform(glm::vec2(0.0f, 0.7f), glm::vec2(0.9f, 0.2f)), Type::Rectangle, "ui_character_header");
	// picturebox with picture of medic
	Label* name = new Label("Medic: ", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.2f, 0.0f), glm::vec2(0.8f, 0.2f)), "ui_character_name");
	// add picturebox child object
	header->AddChildObject(name);

	character_background->AddChildObject(header);
}

void UILayer::ActivateEngineerUI() {
	character_background = new Panel(ui_character_background_color, Transform(glm::vec2(0.85f, 0.0f), ui_background_size), Type::Rectangle, "ui_character_background");

	Panel* header = new Panel(ui_header_color, Transform(glm::vec2(0.0f, 0.7f), glm::vec2(0.9f, 0.2f)), Type::Rectangle, "ui_character_header");
	// picturebox with picture of medic
	Label* name = new Label("Engineer: ", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.2f, 0.0f), glm::vec2(0.8f, 0.2f)), "ui_character_name");
	// add picturebox child object
	header->AddChildObject(name);

	character_background->AddChildObject(header);
}

void UILayer::ActivateMedicBuildlingUI() {
	building_background = new Panel(ui_building_background_color, Transform(glm::vec2(0.15f, 0.0f), ui_background_size), Type::Rectangle, "ui_building_background");

	Panel* header = new Panel(ui_header_color, Transform(glm::vec2(0.0f, 0.7f), glm::vec2(0.9f, 0.2f)), Type::Rectangle, "ui_building_header");
	// picturebox with picture of medic-bulding
	Label* name = new Label("Medic-building: ", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.2f, 0.0f), glm::vec2(0.8f, 0.2f)), "ui_buildling_name");
	// add picturebox child object
	header->AddChildObject(name);

	building_background->AddChildObject(header);
}

void UILayer::ActivateEngineerBuildingUI() {
	building_background = new Panel(ui_building_background_color, Transform(glm::vec2(0.15f, 0.0f), ui_background_size), Type::Rectangle, "ui_building_background");

	Panel* header = new Panel(ui_header_color, Transform(glm::vec2(0.0f, 0.7f), glm::vec2(0.9f, 0.2f)), Type::Rectangle, "ui_building_header");
	// picturebox with picture of medic-bulding
	Label* name = new Label("Engineer-building: ", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.2f, 0.0f), glm::vec2(0.8f, 0.2f)), "ui_buildling_name");
	Button* place_mg_button = new Button(ui_place_mg_button_color, Transform(glm::vec2(0.0f, 0.5f), glm::vec2(0.8f, 0.2f)), Type::Rectangle, Engineer::BuildMG, "ui_place_mg_button");
	// add picturebox child object
	header->AddChildObject(name);
	header->AddChildObject(place_mg_button);

	building_background->AddChildObject(header);
}

void UILayer::DeactivateCharacterUI() {
	RemoveUIObject(character_background);
}

void UILayer::DeactivateBuildingUI() {
	RemoveUIObject(building_background);
}
