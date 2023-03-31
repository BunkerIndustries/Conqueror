#pragma once

#include "_Game.h"

#include "layers/AllyLayer.h"
#include "layers/EnemyLayer.h"
#include "layers/MapLayer.h"
#include "layers/UILayer.h"

#include "utils/WaveManager.h"

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

	GameObject* GetActiveGO() const { return active_go; }
	void SetActiveGO(GameObject* gameObject) { active_go = gameObject; }

	MapLayer* mapLayer = nullptr;
	EnemyLayer* enemyLayer = nullptr;
	AllyLayer* allyLayer = nullptr;
	UILayer* uiLayer = nullptr;

	WaveManager* waveManager = nullptr;

private:
	GameObject* active_go = nullptr;

	void CameraMovement(float dt);
};
