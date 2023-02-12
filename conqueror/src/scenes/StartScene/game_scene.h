#pragma once

#include "Engine.h"
#include "layers/SoundLayer.h"
#include "layers/ForegroundLayer.h"
#include "layers/BackgroundLayer.h"

#include <vector>

class GameScene : public core::Scene
{
private:
	BackgroundLayer* background_layer;
	ForegroundLayer* foreground_layer;
	SoundLayer* sound_layer;

	GameObject* test;
public:
	GameScene();
	virtual ~GameScene() override;
	void loadResources() override;
	void init() override;
	void update(float dt) override;
	void imgui(float dt) override;
	
	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(GameScene::OnMouseScroll));
	};
	bool OnMouseScroll(MouseScrolledEvent& e);

	std::vector<std::vector<GameObject*>> enemy_grid;
};
