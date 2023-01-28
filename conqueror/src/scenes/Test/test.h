#pragma once
#include "Engine.h"
#include "../layers/SoundLayer.h"
#include "../layers/ForegroundLayer.h"
#include "../layers/BackgroundLayer.h"


class testScene : public Scene {

private:
	BackgroundLayer* background_layer;
	ForegroundLayer* foreground_layer;
	SoundLayer* sound_layer;

public:
	testScene();

	void update(float) override;
	void init() override;
	void loadResources() override;

	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(testScene::OnMouseScroll));
		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(testScene::OnMouseClick));

	};

	bool OnMouseScroll(MouseScrolledEvent& e);
	bool OnMouseClick(MouseButtonPressedEvent& e);
};