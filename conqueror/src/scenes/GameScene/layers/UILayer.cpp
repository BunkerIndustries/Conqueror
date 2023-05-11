#include "_Game.h"

#include "UILayer.h"

#include "required/constants.h"
#include "scenes/GameScene/GameScene.h"
#include "utils/Medic.h"
#include "utils/Engineer.h"
#include "utils/Supply.h"

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
	character_background = new Panel(ui_character_background_color, Transform(ui_character_position, ui_background_size), Type::Rectangle, "ui_character_background");

	Panel* header = new Panel(ui_header_color, ui_header_transform, Type::Rectangle, "ui_character_header");
	// picturebox with picture of soldier
	Label* name = new Label("SOLDAT", ui_font_color, ui_header_name_transform, DataPool::GetFont(ui_font_family), "ui_character_name");
	PictureBox* icon = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), ui_character_icon_transform, DataPool::GetTexture("UI/soldier_head.png"), Type::Rectangle);
	Button* call_medic_button = new Button(ui_call_medic_button_color, ui_first_button_transform, Type::Rectangle, Medic::SendMedic, "ui_call_medic_button");
	PictureBox* button_pb = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/medic_button.png"), Type::Rectangle);
	call_medic_button->AddChildObject(button_pb);
	header->AddChildObject(name);

	character_background->AddChildObject(header);
	character_background->AddChildObject(icon);
	character_background->AddChildObject(call_medic_button);

	AddUIObject(character_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateMedicUI() {
	character_background = new Panel(ui_character_background_color, Transform(ui_character_position, ui_background_size), Type::Rectangle, "ui_character_background");

	Panel* header = new Panel(ui_header_color, ui_header_transform, Type::Rectangle, "ui_character_header");
	// picturebox with picture of medic
	Label* name = new Label("ARZT", ui_font_color, ui_header_name_transform, DataPool::GetFont(ui_font_family), "ui_character_name");
	PictureBox* icon = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), ui_character_icon_transform, DataPool::GetTexture("UI/med_head.png"), Type::Rectangle);
	header->AddChildObject(name);

	character_background->AddChildObject(header);
	character_background->AddChildObject(icon);

	AddUIObject(character_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateEngineerUI() {
	character_background = new Panel(ui_character_background_color, Transform(ui_character_position, ui_background_size), Type::Rectangle, "ui_character_background");

	Panel* header = new Panel(ui_header_color, ui_header_transform, Type::Rectangle, "ui_character_header");
	// picturebox with picture of medic
	Label* name = new Label("MECHANIKER", ui_font_color, ui_header_name_transform, DataPool::GetFont(ui_font_family), "ui_character_name");
	PictureBox* icon = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), ui_character_icon_transform, DataPool::GetTexture("UI/engineer_head.png"), Type::Rectangle);
	header->AddChildObject(name);

	character_background->AddChildObject(header);
	character_background->AddChildObject(icon);

	AddUIObject(character_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateMedicBuildlingUI() {
	building_background = new Panel(ui_building_background_color, Transform(ui_building_position, ui_background_size), Type::Rectangle, "ui_building_background");

	Panel* header = new Panel(ui_header_color, ui_header_transform, Type::Rectangle, "ui_building_header");
	// picturebox with picture of medic-bulding
	Label* name = new Label("AERZTE", ui_font_color, ui_header_building_name_transform, DataPool::GetFont(ui_font_family), "ui_buildling_name");
	// add picturebox child object
	header->AddChildObject(name);

	Label* count = new Label(std::to_string(gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->GetAvailableMedics()) + " verfuegbar", ui_font_color, ui_building_count_transform, DataPool::GetFont(ui_font_family));

	building_background->AddChildObject(header);
	building_background->AddChildObject(count);

	AddUIObject(building_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateEngineerBuildingUI() {
	building_background = new Panel(ui_building_background_color, Transform(ui_building_position, ui_background_size), Type::Rectangle, "ui_building_background");

	Panel* header = new Panel(ui_header_color, ui_header_transform, Type::Rectangle, "ui_building_header");
	// picturebox with picture of medic-bulding
	Label* name = new Label("MECHANIKER", ui_font_color, ui_header_building_name_transform, DataPool::GetFont(ui_font_family), "ui_buildling_name");
	Button* place_mg_button = new Button(ui_place_mg_button_color, ui_first_button_transform, Type::Rectangle, Engineer::PlaceMG, "ui_place_mg_button");
	PictureBox* button1_pb = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/mg_button.png"), Type::Rectangle);
	Button* place_artillerie_button = new Button(ui_place_artillerie_button_color, ui_second_button_transform, Type::Rectangle, Engineer::PlaceArtillerie, "ui_place_mg_button");
	PictureBox* button2_pb = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/artillery_button.png"), Type::Rectangle);
	place_mg_button->AddChildObject(button1_pb);
	place_artillerie_button->AddChildObject(button2_pb);
	header->AddChildObject(name);

	Label* count = new Label(std::to_string(gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->GetAvailableMedics()) + " verfuegbar", ui_font_color, ui_building_count_transform, DataPool::GetFont(ui_font_family));
	
	building_background->AddChildObject(header);
	building_background->AddChildObject(place_mg_button);
	building_background->AddChildObject(place_artillerie_button);
	building_background->AddChildObject(count);

	AddUIObject(building_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateSupplyMenuUI() {
	RemoveUIObject(character_background);
	RemoveUIObject(building_background);
	RemoveUIObject(supply_menu_background);

	supply_menu_background = new Panel(ui_supply_menu_background_color, Transform(glm::vec2(0.0f, 0.0f), ui_supply_menu_background_size), Type::Rectangle, "ui_supply_menu_background");
	Label* text = new Label("DU HAST EINEM ANGRIFF STANDGEHALTEN!", ui_font_color, ui_supply_menu_text_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_text");
	Label* text2 = new Label("WAS MOECHTEST DU ANFORDERN?", ui_font_color, ui_supply_menu_text2_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_text2");
	Panel* left_option = new Panel(ui_choice_field_color, Transform(ui_left_choice_field_position, ui_choice_field_size), Type::Rectangle, "ui_supply_menu_left_choice_field");
	Label* left_option_text = new Label("SOLDATEN", ui_font_color, ui_choice_field_text_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_left_choice_text");
	left_option->AddChildObject(left_option_text);
	Label* left_option_count = new Label(std::to_string(Supply::CreateLeftOption()) + "x", ui_font_color, ui_choice_field_count_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_left_choice_count");
	left_option->AddChildObject(left_option_count);
	// picturebox with soldier-image
	Button* left_option_button = new Button(ui_choice_field_button_color, ui_choice_field_button_transform, Type::Rectangle, Supply::TakeLeftOption, "ui_upply_menu_left_choice_button");
	left_option->AddChildObject(left_option_button);

	Panel* right_option = new Panel(ui_choice_field_color, Transform(ui_right_choice_field_position, ui_choice_field_size), Type::Rectangle, "ui_supply_menu_right_choice_field");
	Label* right_option_text = new Label(Supply::CreateRightOption(), ui_font_color, ui_choice_field_text_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_right_choice_text");
	right_option->AddChildObject(right_option_text);
	Label* right_option_count = new Label("1x", ui_font_color, ui_choice_field_count_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_right_choice_count");
	right_option->AddChildObject(right_option_count); 
	// picturebox with image
	Button* right_option_button = new Button(ui_choice_field_button_color, ui_choice_field_button_transform, Type::Rectangle, Supply::TakeRightOption, "ui_upply_menu_right_choice_button");
	right_option->AddChildObject(right_option_button);

	supply_menu_background->AddChildObject(text);
	supply_menu_background->AddChildObject(text2);
	supply_menu_background->AddChildObject(left_option);
	supply_menu_background->AddChildObject(right_option);

	AddUIObject(supply_menu_background, ProjectionMode::SCREEN);
}

void UILayer::DeactivateCharacterUI() {
	RemoveUIObject(character_background);
}

void UILayer::DeactivateBuildingUI() {
	RemoveUIObject(building_background);
}

void UILayer::DeactivateSupplyMenuUI() {
	RemoveUIObject(supply_menu_background);
}