#pragma once

#include "_Game.h"

#include "layers/BackgroundLayer.h"
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
	void SetActiveCharacter(GameObject* new_go) { active_character = new_go; }

	GameObject* GetActiveBuilding() const { return active_building; }
	void SetActiveBuilding(GameObject* new_go) { active_building = new_go; }

	BackgroundLayer* backgroundLayer = nullptr;
	MapLayer* mapLayer = nullptr;
	EnemyLayer* enemyLayer = nullptr;
	AllyLayer* allyLayer = nullptr;
	UILayer* uiLayer = nullptr;

	WaveManager* waveManager = nullptr;

	GameObject* CreateBullet(Layer* layer, GameObject* target, glm::vec2 startPos, glm::vec2 targetPos);

private:
	GameObject* active_character = nullptr;
	GameObject* active_building = nullptr;

	void CameraMovement(float dt);

	int wave_count = 0;
};
