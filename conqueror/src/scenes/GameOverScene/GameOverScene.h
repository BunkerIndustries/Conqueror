#pragma once

#include "_Game.h"

#include "layers/StatLayer.h"


class GameOverScene : public Scene {
public:

	GameOverScene();
	~GameOverScene() override;
	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};


private:
	GameObject* CreateButton(std::string sprite_name, glm::vec2 position, std::string action);
	GameObject* CreateElement(std::string sprite_name, glm::vec2 position, glm::vec2 size);

	glm::vec4 background_color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec2 button_size = glm::vec2(10.0f, 1.7f);
	StatLayer* statLayer = nullptr;

};