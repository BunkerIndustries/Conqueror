#pragma once
#include "layer/Layer.h"

class CreditLayer : public Layer
{
public:

	CreditLayer();
	~CreditLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;

private:
	bool OnGameObjectClick(GameObjectPressedEvent& e);

	GameObject* angelina;
	GameObject* levi;
	GameObject* matthias;
	GameObject* pherel;
	GameObject* gutsche;
};