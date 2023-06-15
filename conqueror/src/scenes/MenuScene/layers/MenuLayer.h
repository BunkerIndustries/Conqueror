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

	static Shr<Sound> menu_theme;

private:
	bool OnGameObjectClick(GameObjectPressedEvent& e);
	
};