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


	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;

public:
	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(GameScene::OnMouseScroll));
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(GameScene::GameObjectPressed));
	};
	bool OnMouseScroll(MouseScrolledEvent& e);
	bool GameObjectPressed(GameObjectPressedEvent& e);

	GameObject* GetActiveCharacter() const { return active_character; }
	void SetActiveCharacter(GameObject* gameObject) { active_character = gameObject; }

	GameObject* GetActiveBuilding() const { return active_building; }
	void SetActiveBuilding(GameObject* gameObject) { active_building = gameObject; }

	MapLayer* mapLayer = nullptr;
	EnemyLayer* enemyLayer = nullptr;
	AllyLayer* allyLayer = nullptr;
	UILayer* uiLayer = nullptr;

	WaveManager* waveManager = nullptr;

private:
	GameObject* active_character = nullptr;
	GameObject* active_building = nullptr;

	void CameraMovement(float dt);
};
