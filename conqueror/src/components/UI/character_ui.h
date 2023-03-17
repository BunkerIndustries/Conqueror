#pragma once
#include "Engine.h"

class CharacterUI : public Component {
public:
	CharacterUI();
	virtual ~CharacterUI() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;

	void event(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(CharacterUI::UIElementPressed));
	};
	bool UIElementPressed(GameObjectPressedEvent& e);

	void ToggleUI();

private:
	void CreateBackground();
	void DeleteUI();

	bool ui_toggled = false;
	std::vector<GameObject*> ui_elements;
};