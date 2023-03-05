#pragma once

#include "Engine.h"
#include "layers/SoundLayer.h"
#include "layers/ForegroundLayer.h"
#include "layers/BackgroundLayer.h"

#include <vector>

class GameScene : public core::Scene
{
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
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(GameScene::GameObjectPressed));
	};
	bool OnMouseScroll(MouseScrolledEvent& e);
	bool GameObjectPressed(GameObjectPressedEvent& e);

private:
	GameObject* active_go{ nullptr };
};
