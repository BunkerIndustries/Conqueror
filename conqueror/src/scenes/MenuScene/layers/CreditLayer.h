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
	GameObject* angelina_text;

	GameObject* levi;
	GameObject* levi_text;

	GameObject* matthias;
	GameObject* matthias_text;

	GameObject* pherel;
	GameObject* pherel_text;

	GameObject* gutsche;
	GameObject* gutsche_text;
};