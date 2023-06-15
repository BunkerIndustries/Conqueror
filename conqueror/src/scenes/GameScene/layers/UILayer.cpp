#include "_Game.h"

#include "UILayer.h"

#include "required/constants.h"
#include "scenes/GameScene/GameScene.h"
#include "utils/Medic.h"
#include "utils/Engineer.h"
#include "utils/Supply.h"
#include "utils/Economy.h"

UILayer::UILayer()
	: Layer("UILayer")
{
}

UILayer::~UILayer()
{
}

void UILayer::OnAttach()
{
	AddCountdown();
	AddMoney();
	AddSoldierCount();
}

void UILayer::OnDetach()
{
}

void UILayer::Update(const float dt)
{
	UpdateDeathCountdown();
	UpdateMoney();
	UpdateSoldierCount();
}


void UILayer::ActivateSoldierUI() {
	character_background = new PictureBox(white_color, Transform(ui_character_position, ui_background_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);

	PictureBox* header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	// picturebox with picture of soldier
	Label* name = new Label(gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->GetName(), ui_font_color, ui_header_name_transform, DataPool::GetFont(ui_font_family), "ui_character_name");
	PictureBox* icon = new PictureBox(white_color, ui_character_icon_transform, DataPool::GetTexture("UI/soldier_head.png"), Type::Rectangle);

	PictureBox* hp_icon = new PictureBox(white_color, ui_hp_icon_transform, DataPool::GetTexture("UI/HP_icon_clear.png"), Type::Rectangle, "hp_icon");
	hp = gameScene->GetActiveCharacter()->GetComponent<Health>()->GetHp();
	hp_text = new Label(std::to_string(hp), ui_font_color, ui_health_text_transform, DataPool::GetFont(ui_font_family), "hp_text");
	character_background->AddChildObject(hp_icon);
	character_background->AddChildObject(hp_text);


	Button* call_medic_button = new Button(white_color, ui_medic_button_transform, Type::Rectangle, Medic::SendMedic, "ui_call_medic_button");
	PictureBox* button_pb = new PictureBox(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/medic_button.png"), Type::Rectangle);
	call_medic_button->AddChildObject(button_pb);
	header->AddChildObject(name);

	
	character_background->AddChildObject(header);
	character_background->AddChildObject(icon);
	character_background->AddChildObject(call_medic_button);

	AddUIObject(character_background, ProjectionMode::SCREEN);

	// upgrade menu //

	soldier_upgrade_background = new PictureBox(white_color, Transform(glm::vec2(0.8f, -0.55f), upgrade_box_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);
	PictureBox* u_header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	Label* u_name = new Label("UPGRADE", ui_font_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.16f, 0.63f)), DataPool::GetFont(ui_font_family));
	u_header->AddChildObject(u_name); 
	soldier_upgrade_background->AddChildObject(u_header);

	soldier_upgrade_price = new Label(std::to_string(gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->GetUpgradePrice()), ui_font_color, Transform(glm::vec2(-0.6f, -0.3f), glm::vec2(0.15f, 0.45f)), DataPool::GetFont(ui_font_family));
	PictureBox* coin = new PictureBox(white_color, Transform(glm::vec2(-0.15f, -0.3f), glm::vec2(0.16f, 0.32f)), DataPool::GetTexture("UI/coin.png"), Type::Rectangle);
	Button* buy = new Button(white_color, Transform(glm::vec2(0.5f, -0.3f), glm::vec2(0.22f, 0.34f)), Type::Rectangle, UILayer::UpgradeSoldier, "soldier_buy_button");
	PictureBox* buy_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/upgrade_button.png"), Type::Rectangle);
	buy->AddChildObject(buy_pb);
	soldier_upgrade_background->AddChildObject(soldier_upgrade_price); soldier_upgrade_background->AddChildObject(coin); soldier_upgrade_background->AddChildObject(buy);

	AddUIObject(soldier_upgrade_background, ProjectionMode::SCREEN);
	/*Label* upg1_t = new Label("Genauigkeit", white_color, Transform(glm::vec2(-0.5f, 0.2f), glm::vec2(0.2f, 0.1f)), DataPool::GetFont(ui_font_family));
	Label* upg1_p = new Label("10", white_color, Transform(glm::vec2(0.2f, 0.8f), glm::vec2(0.2f, 0.1f)), DataPool::GetFont(ui_font_family));*/
}

void UILayer::ActivateMedicUI() {
	character_background = new PictureBox(white_color, Transform(ui_character_position, ui_background_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);

	PictureBox* header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);	// picturebox with picture of medic
	Label* name = new Label(gameScene->GetActiveCharacter()->GetComponent<MedicCharacter>()->GetName(), ui_font_color, ui_header_name_transform, DataPool::GetFont(ui_font_family), "ui_character_name");
	PictureBox* icon = new PictureBox(white_color, ui_character_icon_transform, DataPool::GetTexture("UI/med_head.png"), Type::Rectangle);
	header->AddChildObject(name);

	PictureBox* hp_icon = new PictureBox(white_color, ui_hp_icon_transform, DataPool::GetTexture("UI/HP_icon_clear.png"), Type::Rectangle, "hp_icon");
	hp = gameScene->GetActiveCharacter()->GetComponent<Health>()->GetHp();
	hp_text = new Label(std::to_string(hp), ui_font_color, ui_health_text_transform, DataPool::GetFont(ui_font_family), "hp_text");
	character_background->AddChildObject(hp_icon);
	character_background->AddChildObject(hp_text);

	character_background->AddChildObject(header);
	character_background->AddChildObject(icon);

	AddUIObject(character_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateEngineerUI() {
	character_background = new PictureBox(white_color, Transform(ui_character_position, ui_background_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);

	PictureBox* header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);	// picturebox with picture of medic
	Label* name = new Label(gameScene->GetActiveCharacter()->GetComponent<MedicCharacter>()->GetName(), ui_font_color, ui_header_building_name_transform, DataPool::GetFont(ui_font_family), "ui_character_name");
	PictureBox* icon = new PictureBox(white_color, ui_character_icon_transform, DataPool::GetTexture("UI/engineer_head.png"), Type::Rectangle);
	header->AddChildObject(name);

	PictureBox* hp_icon = new PictureBox(white_color, ui_hp_icon_transform, DataPool::GetTexture("UI/HP_icon_clear.png"), Type::Rectangle, "hp_icon");
	hp = gameScene->GetActiveCharacter()->GetComponent<Health>()->GetHp();
	hp_text = new Label(std::to_string(hp), ui_font_color, ui_health_text_transform, DataPool::GetFont(ui_font_family), "hp_text");
	character_background->AddChildObject(hp_icon);
	character_background->AddChildObject(hp_text);

	character_background->AddChildObject(header);
	character_background->AddChildObject(icon);

	AddUIObject(character_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateMedicBuildlingUI() {
	building_background = new PictureBox(white_color, Transform(ui_building_position, ui_building_background_size), DataPool::GetTexture("UI/box_2.png"), Type::Rectangle);

	PictureBox* header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);	// picturebox with picture of medic-bulding
	Label* name = new Label("AERZTE", ui_font_color, ui_header_building_name_transform, DataPool::GetFont(ui_font_family), "ui_buildling_name");
	PictureBox* icon = new PictureBox(white_color, ui_building_icon_transform, DataPool::GetTexture("UI/med_icon_clear.png"), Type::Rectangle);
	header->AddChildObject(name);

	Label* count = new Label(std::to_string(gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->GetAvailableMedics()) + " verfuegbar", ui_font_color, ui_building_count_transform, DataPool::GetFont(ui_font_family));

	building_background->AddChildObject(header);
	building_background->AddChildObject(count);
	building_background->AddChildObject(icon);

	AddUIObject(building_background, ProjectionMode::SCREEN);

	// upgrade menu //

	medic_building_upgrade_background = new PictureBox(white_color, Transform(glm::vec2(-0.8f, -0.55f), upgrade_box_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);
	PictureBox* u_header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	Label* u_name = new Label("UPGRADE", ui_font_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.16f, 0.55f)), DataPool::GetFont(ui_font_family));
	u_header->AddChildObject(u_name);
	medic_building_upgrade_background->AddChildObject(u_header);

	medic_building_upgrade_price = new Label(std::to_string(medic_building_upgrade_price_float), ui_font_color, Transform(glm::vec2(-0.6f, -0.3f), glm::vec2(0.15f, 0.45f)), DataPool::GetFont(ui_font_family));
	PictureBox* coin = new PictureBox(white_color, Transform(glm::vec2(-0.15f, -0.3f), glm::vec2(0.16f, 0.32f)), DataPool::GetTexture("UI/coin.png"), Type::Rectangle);
	Button* buy = new Button(white_color, Transform(glm::vec2(0.5f, -0.3f), glm::vec2(0.22f, 0.34f)), Type::Rectangle, UILayer::UpgradeMedBuilding, "medic_buy_button");
	PictureBox* buy_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/upgrade_button.png"), Type::Rectangle);
	buy->AddChildObject(buy_pb);
	medic_building_upgrade_background->AddChildObject(medic_building_upgrade_price); medic_building_upgrade_background->AddChildObject(coin); medic_building_upgrade_background->AddChildObject(buy);

	AddUIObject(medic_building_upgrade_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateSoldierBuildingUI() {

	soldier_building_upgrade_background = new PictureBox(white_color, Transform(glm::vec2(-0.8f, 0.0f), upgrade_box_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);
	PictureBox* u_header = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.57f), glm::vec2(0.9f, 0.3f)), DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	Label* u_name = new Label("SOLDATEN\nUPGRADE", ui_font_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.13f, 0.42f)), DataPool::GetFont(ui_font_family));
	u_header->AddChildObject(u_name);
	soldier_building_upgrade_background->AddChildObject(u_header);

	Label* soldier_building_upgrade_price = new Label(std::to_string(soldier_building_upgrade_price_float), ui_font_color, Transform(glm::vec2(-0.6f, -0.3f), glm::vec2(0.15f, 0.45f)), DataPool::GetFont(ui_font_family));
	PictureBox* coin = new PictureBox(white_color, Transform(glm::vec2(-0.15f, -0.3f), glm::vec2(0.16f, 0.32f)), DataPool::GetTexture("UI/coin.png"), Type::Rectangle);
	soldier_upgrade_buy = new Button(white_color, Transform(glm::vec2(0.5f, -0.3f), glm::vec2(0.22f, 0.34f)), Type::Rectangle, nullptr);
	PictureBox* buy_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/upgrade_button.png"), Type::Rectangle);
	soldier_upgrade_buy->AddChildObject(buy_pb);
	soldier_building_upgrade_background->AddChildObject(soldier_building_upgrade_price); soldier_building_upgrade_background->AddChildObject(coin); soldier_building_upgrade_background->AddChildObject(soldier_upgrade_buy);

	AddUIObject(soldier_building_upgrade_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateEngineerBuildingUI() {
	building_background = new PictureBox(white_color, Transform(ui_building_position, ui_building_background_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);

	PictureBox* header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);	// picturebox with picture of medic-bulding
	Label* name = new Label("MECHANIKER", ui_font_color, ui_header_building_name_transform, DataPool::GetFont(ui_font_family), "ui_buildling_name");
	PictureBox* icon = new PictureBox(white_color, ui_building_icon_transform, DataPool::GetTexture("UI/engineer_icon_clear.png"), Type::Rectangle);
	Button* place_mg_button = new Button(white_color, ui_first_button_transform, Type::Rectangle, Engineer::PlaceMG, "ui_place_mg_button");
	PictureBox* button1_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/mg_button.png"), Type::Rectangle);
	Button* place_artillerie_button = new Button(white_color, ui_second_button_transform, Type::Rectangle, Engineer::PlaceArtillerie, "ui_place_mg_button");
	PictureBox* button2_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/artillery_button.png"), Type::Rectangle);
	place_mg_button->AddChildObject(button1_pb);
	place_artillerie_button->AddChildObject(button2_pb);
	header->AddChildObject(name);

	Label* count = new Label(std::to_string(gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->GetAvailableEngineers()) + " verfuegbar", ui_font_color, ui_building_count_transform, DataPool::GetFont(ui_font_family));
	Label* mgCount = new Label(std::to_string(gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->GetMgStock()) + "x", ui_font_color, Transform(glm::vec2(0.5f, -0.2f), glm::vec2(0.15, 0.15)), DataPool::GetFont(ui_font_family));
	Label* artillerieCount = new Label(std::to_string(gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->GetArtilleryStock()) + "x", ui_font_color, Transform(glm::vec2(0.5f, -0.7f), glm::vec2(0.15, 0.15)), DataPool::GetFont(ui_font_family));
	
	building_background->AddChildObject(header);
	building_background->AddChildObject(place_mg_button);
	building_background->AddChildObject(place_artillerie_button);
	building_background->AddChildObject(count);
	building_background->AddChildObject(mgCount);
	building_background->AddChildObject(artillerieCount);
	building_background->AddChildObject(icon);

	AddUIObject(building_background, ProjectionMode::SCREEN);

	// upgrade menu //

	engineer_building_upgrade_background = new PictureBox(white_color, Transform(glm::vec2(-0.8f, -0.55f), upgrade_box_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);
	PictureBox* u_header = new PictureBox(white_color, ui_header_transform, DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	Label* u_name = new Label("UPGRADE", ui_font_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.16f, 0.55f)), DataPool::GetFont(ui_font_family));
	u_header->AddChildObject(u_name);
	engineer_building_upgrade_background->AddChildObject(u_header);

	engineer_building_upgrade_price = new Label(std::to_string(engineer_building_upgrade_price_float), ui_font_color, Transform(glm::vec2(-0.6f, -0.3f), glm::vec2(0.15f, 0.45f)), DataPool::GetFont(ui_font_family));
	PictureBox* coin = new PictureBox(white_color, Transform(glm::vec2(-0.15f, -0.3f), glm::vec2(0.16f, 0.32f)), DataPool::GetTexture("UI/coin.png"), Type::Rectangle);
	Button* buy = new Button(white_color, Transform(glm::vec2(0.5f, -0.3f), glm::vec2(0.22f, 0.34f)), Type::Rectangle, UILayer::UpgradeEngineerBuilding, "engineer_buy_button");
	PictureBox* buy_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/upgrade_button.png"), Type::Rectangle);
	buy->AddChildObject(buy_pb);
	engineer_building_upgrade_background->AddChildObject(engineer_building_upgrade_price); engineer_building_upgrade_background->AddChildObject(coin); engineer_building_upgrade_background->AddChildObject(buy);

	AddUIObject(engineer_building_upgrade_background, ProjectionMode::SCREEN);
}

void UILayer::ActivateSupplyMenuUI() {
	RemoveUIObject(character_background);
	RemoveUIObject(building_background);
	RemoveUIObject(supply_menu_background);

	supply_menu_background = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), ui_supply_menu_background_size), DataPool::GetTexture("UI/big_box.png"), Type::Rectangle);

	Label* text = new Label("DU HAST EINEM ANGRIFF STANDGEHALTEN!", ui_font_color, ui_supply_menu_text_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_text");
	Label* text2 = new Label("WAS MOECHTEST DU ANFORDERN?", ui_font_color, ui_supply_menu_text2_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_text2");

	PictureBox* left_option = new PictureBox(white_color, Transform(ui_left_choice_field_position, ui_choice_field_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);

	Label* left_option_text = new Label("SOLDATEN", ui_font_color, ui_choice_field_text_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_left_choice_text");
	left_option->AddChildObject(left_option_text);
	Label* left_option_count = new Label(std::to_string(Supply::CreateLeftOption()) + "x", ui_font_color, ui_choice_field_count_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_left_choice_count");
	left_option->AddChildObject(left_option_count);
	// picturebox with soldier-image
	Button* left_option_button = new Button(white_color, ui_choice_field_button_transform, Type::Rectangle, Supply::TakeLeftOption, "ui_upply_menu_left_choice_button");
	PictureBox* button1_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	Label* left_option_button_text = new Label("Anfordern", ui_font_color, Transform(glm::vec2(0.0f, 0.0f), anfordern_button_size), DataPool::GetFont(ui_font_family));
	
	left_option_button->AddChildObject(button1_pb);
	left_option_button->AddChildObject(left_option_button_text);
	left_option->AddChildObject(left_option_button);

	Label* wave = new Label(std::to_string(gameScene->waveManager->GetWaveCount()), ui_font_color, ui_wave_count_transform, DataPool::GetFont(ui_font_family), "ui_wave_count_transform");
	supply_menu_background->AddChildObject(wave);

	PictureBox* right_option = new PictureBox(white_color, Transform(ui_right_choice_field_position, ui_choice_field_size), DataPool::GetTexture("UI/box_1.png"), Type::Rectangle);
	Label* right_option_text = new Label(Supply::CreateRightOption(), ui_font_color, ui_choice_field_text_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_right_choice_text");
	right_option->AddChildObject(right_option_text);
	Label* right_option_count = new Label("1x", ui_font_color, ui_choice_field_count_transform, DataPool::GetFont(ui_font_family), "ui_supply_menu_right_choice_count");
	right_option->AddChildObject(right_option_count); 
	Button* right_option_button = new Button(white_color, ui_choice_field_button_transform, Type::Rectangle, Supply::TakeRightOption, "ui_upply_menu_right_choice_button");
	PictureBox* button2_pb = new PictureBox(white_color, Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), DataPool::GetTexture("UI/box_small.png"), Type::Rectangle);
	Label* right_option_button_text = new Label("Anfordern", ui_font_color, Transform(glm::vec2(0.0f, 0.0f), anfordern_button_size), DataPool::GetFont(ui_font_family));
	
	right_option_button->AddChildObject(button2_pb);
	right_option_button->AddChildObject(right_option_button_text);
	right_option->AddChildObject(right_option_button);

	supply_menu_background->AddChildObject(text);
	supply_menu_background->AddChildObject(text2);
	supply_menu_background->AddChildObject(left_option);
	supply_menu_background->AddChildObject(right_option);

	AddUIObject(supply_menu_background, ProjectionMode::SCREEN);
}

void UILayer::DeactivateCharacterUI() {
	RemoveUIObject(character_background);
	RemoveUIObject(soldier_upgrade_background);
}

void UILayer::DeactivateBuildingUI() {
	RemoveUIObject(building_background);
	RemoveUIObject(medic_building_upgrade_background);
	RemoveUIObject(engineer_building_upgrade_background);
	RemoveUIObject(soldier_building_upgrade_background);
}

void UILayer::DeactivateSupplyMenuUI() {
	RemoveUIObject(supply_menu_background);
}

void UILayer::AddCountdown() {
	countDown = new Label(std::to_string(loss_countdown), ui_font_color, Transform(glm::vec2(0.85f, 0.85f), glm::vec2(0.15f, 0.15f)), DataPool::GetFont(ui_font_family), "ui_death_countdown");
	AddUIObject(countDown, ProjectionMode::SCREEN);
}
void UILayer::AddMoney() {
	money = new Label("0", ui_font_color, Transform(glm::vec2(-0.9f, 0.9f), glm::vec2(0.075f, 0.075f)), DataPool::GetFont(ui_font_family), "ui_money");
	coin = new PictureBox(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), Transform(glm::vec2(-0.8f, 0.9f), glm::vec2(0.075f, 0.075f)), DataPool::GetTexture("UI/coin.png"), Type::Rectangle);
	AddUIObject(money, ProjectionMode::SCREEN);
	AddUIObject(coin, ProjectionMode::SCREEN);
}


void UILayer::UpdateDeathCountdown() {
	static float i;
	i += Application::GetDT();
	if (i > 1) {
		i--;
		if (filled_last_row_grid_positions.size() > 0) {
			loss_countdown -= filled_last_row_grid_positions.size();
			countDown->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.8f));
		}
		else if (filled_last_row_grid_positions.size() == 0 && loss_countdown == 60) {
			return;
		}
		else if (filled_last_row_grid_positions.size() == 0) {
			loss_countdown++;
			countDown->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.8f));
		}
	}
	else if(i > 0.3f){
		countDown->SetColor(ui_font_color);
	}
	countDown->text = std::to_string(loss_countdown);
	if (loss_countdown <= 0) {
		delete gameOverScene;
		gameOverScene = new GameOverScene();
		Application::ChangeScene(gameOverScene, false);
	}
}

void UILayer::AddSoldierCount() {
	soldierCount = new Label(std::to_string(Supply::GetSoldiers()), ui_font_color, Transform(glm::vec2(-0.9f, 0.8f), glm::vec2(0.075f, 0.075f)), DataPool::GetFont(ui_font_family), "ui_soldier_count");
	soldierPic = new PictureBox(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), Transform(glm::vec2(-0.8f, 0.8f), glm::vec2(0.075f, 0.075f)), DataPool::GetTexture("UI/soldier_head.png"), Type::Rectangle);
	AddUIObject(soldierCount, ProjectionMode::SCREEN);
	AddUIObject(soldierPic, ProjectionMode::SCREEN);
}

void UILayer::UpdateSoldierCount() {
	soldierCount->text = std::to_string(Supply::GetSoldiers());
}
void UILayer::UpdateMoney() {
	money->text = std::to_string(Economy::getBalance());
}

bool UILayer::UpgradeSoldier() {
	int oldLevel = gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->GetLevel();
	int oldPrice = gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->GetUpgradePrice();
	int price = 5 + oldPrice + 10 * oldLevel;
	if (oldLevel <= max_soldier_level && Economy::getBalance() - oldPrice >= 0) {
		gameScene->GetActiveCharacter()->GetComponent<SoldierShooting>()->UpgradeSoldier();
		Economy::RemoveBalance(price);
		gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->SetUpgradePrice(5 + oldLevel * 10 + price);
		gameScene->uiLayer->DeactivateCharacterUI();
		gameScene->uiLayer->ActivateSoldierUI();
		if (gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->GetLevel() == 5) {
			gameScene->uiLayer->soldier_upgrade_price->text = "MAX";
			gameScene->uiLayer->RemoveUIObject(gameScene->uiLayer->soldier_upgrade_buy);
		}
	}
	return true;
}
bool UILayer::UpgradeMedBuilding() {
	if (gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->building_level <= max_medic_building_level) {
		gameScene->mapLayer->medicBuilding->GetComponent<MedicBuilding>()->UpgradeBuilding();
	}
	
	return true;
}
bool UILayer::UpgradeEngineerBuilding() {
	gameScene->mapLayer->engineerBuilding->GetComponent<EngineerBuilding>()->UpgradeBuilding();
	return true;
}
void UILayer::UpgradeSoldierTent() {
	//gameScene->GetActiveCharacter()->GetComponent<SoldierShooting>()->UpgradeSoldier();
}