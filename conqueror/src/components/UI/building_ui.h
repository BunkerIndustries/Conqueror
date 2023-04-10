#pragma once
#include "Engine.h"

class BuildingUI : public Component {
public:
	BuildingUI();
	virtual ~BuildingUI() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;

	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(BuildingUI::UIElementPressed));
	};
	bool UIElementPressed(GameObjectPressedEvent& e);

	void OpenUI();
	void DeleteUI();

private:
	void CreateBackground();
	void CreateHeader();
	void CreateButtons();

	std::vector<GameObject*> building_ui_elements;
};