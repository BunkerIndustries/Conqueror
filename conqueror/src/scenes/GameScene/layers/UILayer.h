#pragma once
#include "layer/Layer.h"

class UILayer : public Layer
{
public:

	UILayer();
	~UILayer() override;

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
	Label* countDown;
	Label* money;
	Label* soldier_upgrade_price;
	Label* medic_building_upgrade_price;
	Label* engineer_building_upgrade_price;
	Label* soldier_building_upgrade_price;
	Button* soldier_building_upgrade_buy;
	PictureBox* coin;
	PictureBox* soldierPic;

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