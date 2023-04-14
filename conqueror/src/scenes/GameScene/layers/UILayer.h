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
	void ActivateMedicBuildlingUI();
	void ActivateEngineerBuildingUI();
	void DeactivateCharacterUI();
	void DeactivateBuildingUI();

private:
	Panel* character_background;
	Panel* building_background;
};