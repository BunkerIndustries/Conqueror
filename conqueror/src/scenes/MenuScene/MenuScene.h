#pragma once

#include "_Game.h"
#include "layers/MenuLayer.h"
#include "layers/MenuBackgroundLayer.h"
#include "layers/CreditLayer.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene() override;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& e) override {}

	void CreditsStart();
	void CreditsStop();

	MenuLayer* menuLayer = nullptr;
	MenuBackgroundLayer* menuBackgroundLayer = nullptr;
	CreditLayer* creditLayer = nullptr;

private:
	GameObject* CreateButton(std::string sprite_name, glm::vec2 position, std::string action);
	GameObject* CreateElement(std::string sprite_name, glm::vec2 position, glm::vec2 size);
	GameObject* CreateResetButton(glm::vec2 position);

	glm::vec4 background_color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec2 button_size = glm::vec2(10.0f, 1.7f);


};
