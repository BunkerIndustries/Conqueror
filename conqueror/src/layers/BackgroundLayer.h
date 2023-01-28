#pragma once
#include "Engine.h"

class BackgroundLayer : public Layer
{
private:
	GameObject* background1;
	GameObject* background2;
	GameObject* background3;
	GameObject* background4;
	GameObject* background5;
	GameObject* background6;
	GameObject* background7;
	GameObject* background8;
public:
	BackgroundLayer()
		: Layer("Background") { }

	virtual ~BackgroundLayer() = default;

	void OnAttach() override;
	void OnDetach() override;
	void update(const float dt) override;
	void imgui(const float dt) override;
	void OnEvent(Event& event) override;
};

