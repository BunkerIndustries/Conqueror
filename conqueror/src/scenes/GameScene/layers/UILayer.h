#pragma once
#include "layer/Layer.h"

class UILayer : public Layer
{
public:

	UILayer();
	~UILayer() override;

	void Load();

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override {};

	void ActivateSoldierUI();
	void ActivateMedicUI();
	void ActivateEngineerUI();
	void ActivateMedicBuildingUI();
	void ActivateEngineerBuildingUI();
	void ActivateSupplyMenuUI();
	void DeactivateCharacterUI();
	void DeactivateBuildingUI();
	void DeactivateSupplyMenuUI();
	void ActivateSoldierBuildingUI();
	void DeactivateSoldierBuildingUI();

	void UpdateDeathCountdown();
	void AddCountdown();
	void AddMoney();
	void UpdateMoney();

	static bool UpgradeSoldier();
	static bool UpgradeMedBuilding();
	static bool UpgradeEngineerBuilding();
	static bool UpgradeSoldierTent();

	static bool BuySoldier();
	static bool BuyMg();
	static bool BuyArtillary();

	Label* countDown = nullptr;
	Label* money = nullptr;
	Label* soldier_upgrade_price = nullptr;
	Label* medic_building_upgrade_price = nullptr;
	Label* engineer_building_upgrade_price = nullptr;
	Label* soldier_building_upgrade_price = nullptr;
	Button* soldier_building_upgrade_buy = nullptr;
	PictureBox* coin = nullptr;
	PictureBox* soldierPic = nullptr;

	static void Init();

	static Shr<Sound> sound_upgrade;
	static Shr<Sound> sound_time;

	Button* soldier_upgrade_buy;


private:
	PictureBox* character_background;
	PictureBox* building_background;
	PictureBox* supply_menu_background;

	PictureBox* soldier_upgrade_background;
	PictureBox* medic_building_upgrade_background;
	PictureBox* engineer_building_upgrade_background;
	PictureBox* soldier_building_upgrade_background;
	PictureBox* soldier_building_shop_background;

	void UpdateSoldierCount();
	void AddSoldierCount();
	Label* soldierCount;

	
	int hp;
	Label* hp_text;
};