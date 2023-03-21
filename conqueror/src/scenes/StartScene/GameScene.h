#pragma once

#include "Engine.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene() override;
	void LoadResources() override;
	void Init() override;
	void Update() override;
	
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
