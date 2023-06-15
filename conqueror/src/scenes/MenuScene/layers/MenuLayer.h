#pragma once
#include "layer/Layer.h"

class MenuLayer : public Layer
{
public:

	MenuLayer();
	~MenuLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;

	static void ResetButton();

private:
	bool OnGameObjectClick(GameObjectPressedEvent& e);

	GameObject* reset = nullptr;
};