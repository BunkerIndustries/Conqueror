#pragma once
#include "layer/Layer.h"

class MenuLayer : public Layer
{
public:

	MenuLayer();
	~MenuLayer() override;

	static void Init();

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;

private:
	bool OnGameObjectClick(GameObjectPressedEvent& e);
	static Shr<Sound> menu_theme;
	static Shr<Sound> menu_select;
};