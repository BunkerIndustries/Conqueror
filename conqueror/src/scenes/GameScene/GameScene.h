#pragma once

#include "Engine.h"

#include "layers/AllyLayer.h"
#include "layers/EnemyLayer.h"
#include "layers/MapLayer.h"
#include "layers/UILayer.h"
#include "layers/ForegroundLayer.h"

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

	MapLayer* mapLayer = nullptr;
	EnemyLayer* enemyLayer = nullptr;
	AllyLayer* allyLayer = nullptr;
	UILayer* uiLayer = nullptr;

	ForegroundLayer* fgl = nullptr;

private:
	GameObject* active_go = nullptr;

	void CameraMovement(float dt);
};
