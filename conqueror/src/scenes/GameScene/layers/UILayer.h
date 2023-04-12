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
	void OnEvent(Event& event) override;

	void test();

private:
	bool OnGameObjectClick(GameObjectPressedEvent& e);

	void OnUIClick();
	void OnGOClick(GameObject* gameObject);
};