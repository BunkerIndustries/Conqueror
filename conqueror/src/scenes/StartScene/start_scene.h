#pragma once

#include "Engine.h"
#include "layers/SoundLayer.h"
#include "layers/ForegroundLayer.h"
#include "layers/BackgroundLayer.h"

class StartScene : public core::Scene
{
private:
	BackgroundLayer* background_layer;
	ForegroundLayer* foreground_layer;
	SoundLayer* sound_layer;

	GameObject* test;
public:
	StartScene();
	virtual ~StartScene() override;
	void loadResources() override;
	void init() override;
	void update(float dt) override;
	void imgui(float dt) override;
	
	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(StartScene::OnMouseScroll));
	};
	bool OnMouseScroll(MouseScrolledEvent& e);
};
