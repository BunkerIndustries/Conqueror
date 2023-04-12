#include "_Game.h"

#include "UILayer.h"

#include "required/constants.h"
#include "scenes/GameScene/GameScene.h"
#include "utils/Medic.h"

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
	character_background = new Panel(ui_character_background_color, Transform(glm::vec2(0.0f, 0.85f), ui_background_size), Type::Rectangle, "ui_background");

	Panel* header = new Panel(ui_header_color, Transform(glm::vec2(0.0f, 0.7f), glm::vec2(0.9f, 0.2f)), Type::Rectangle, "ui_header");
	// picturebox with picture of soldier
	Label* name = new Label("Soldat: ", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.2f, 0.0f), glm::vec2(0.8f, 0.2f)), "ui_name");
	Button* call_medic_button = new Button(ui_call_medic_button_color, Transform(glm::vec2(0.0f, 0.5f), glm::vec2(0.8f, 0.2f)), Type::Rectangle, Medic::SendMedic, "ui_call_medic_button");
	// add picturebox child object
	header->AddChildObject(name); 
	header->AddChildObject(call_medic_button);

	character_background->AddChildObject(header);
}

void UILayer::ActivateMedicUI() {

}

void UILayer::ActivateEngineerUI() {

}

void UILayer::ActivateMedicBuildlingUI() {

}

void UILayer::ActivateEngineerBuildingUI() {

}

void UILayer::DeactivateCharacterUI() {
	RemoveUIObject(character_background);
}

void UILayer::DeactivateBuildingUI() {
	RemoveUIObject(building_background);
}
