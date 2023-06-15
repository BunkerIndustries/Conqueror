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
	void ActivateMedicBuildlingUI();
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
	static void UpgradeSoldierTent();
	Label* countDown;
	Label* money;
	PictureBox* coin;
	PictureBox* soldierPic;


private:
	PictureBox* character_background;
	PictureBox* building_background;
	PictureBox* supply_menu_background;

	PictureBox* soldier_upgrade_background;
	PictureBox* medic_building_upgrade_background;
	PictureBox* engineer_building_upgrade_background;
	PictureBox* soldier_building_upgrade_background;

	void UpdateSoldierCount();
	void AddSoldierCount();
	Label* soldierCount;
	
	int hp;
	Label* hp_text;
};