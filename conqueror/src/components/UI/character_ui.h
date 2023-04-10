#pragma once
#include "Engine.h"

class CharacterUI : public Component {
public:
	CharacterUI();
	virtual ~CharacterUI() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;

	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(CharacterUI::UIElementPressed));
	};
	bool UIElementPressed(GameObjectPressedEvent& e);

	void OpenUI();
	void DeleteUI();

private:
	void CreateBackground();
	void CreateHeader();
	void CreateButtons();

	std::vector<GameObject*> ui_elements;
};