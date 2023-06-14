#include "_Game.h"
#include "GameOverScene.h"

#include "required/constants.h"

GameOverScene::GameOverScene() {
	statLayer = new StatLayer();

	CreateButton("quite_button.png", glm::vec2(0.0f, -3.0f), "menu");

}

GameOverScene::~GameOverScene() {

}

void GameOverScene::OnStart(){
	AddLayer(statLayer);

}

void GameOverScene::OnStop() {
	RemoveLayer(statLayer);
}

void GameOverScene::OnUpdate() {}

GameObject* GameOverScene::CreateElement(std::string sprite_name, glm::vec2 position, glm::vec2 size) {

    GameObject* element = new GameObject("menu_element", Transform(position, size));
    element->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("MainMenu/" + sprite_name), 1.0f, Geometry::RECTANGLE));
    statLayer->AddGameObjectToLayer(element);
    return element;
}

GameObject* GameOverScene::CreateButton(std::string sprite_name, glm::vec2 position, std::string action) {

    GameObject* button = new GameObject("menu_button", Transform(position, button_size));
    button->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("MainMenu/" + sprite_name), 1.0f, Geometry::RECTANGLE, true));
    button->AddTag(action);
    statLayer->AddGameObjectToLayer(button);
    return button;
}