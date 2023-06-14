#include "_Game.h"

#include "MenuScene.h"
#include "../GameScene/GameScene.h"


MenuScene::MenuScene() {
    backcolor = background_color;

    menuLayer = new MenuLayer();

    CreateElement("title_object_001.png", glm::vec2(0.0f, 3.0f), glm::vec2(11.0f, 3.0f));
    CreateButton("play_object_001.png", glm::vec2(0.0f, -1.0f), "play");
    CreateButton("quit_button.png", glm::vec2(0.0f, -3.0f), "quit");
}
 
MenuScene::~MenuScene() {
}

void MenuScene::OnStart() {
    AddLayer(menuLayer);
}

void MenuScene::OnStop() {
    RemoveLayer(menuLayer);
}

void MenuScene::OnUpdate() {

}

GameObject* MenuScene::CreateElement(std::string sprite_name, glm::vec2 position, glm::vec2 size) {

    GameObject* element = new GameObject("menu_element", Transform(position, size));
    element->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("MainMenu/" + sprite_name), 1.0f, Geometry::RECTANGLE));
    menuLayer->AddGameObjectToLayer(element);
    return element;
}

GameObject* MenuScene::CreateButton(std::string sprite_name, glm::vec2 position, std::string action) {
    
    GameObject* button = new GameObject("menu_button", Transform(position, button_size));
    button->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("MainMenu/" + sprite_name), 1.0f, Geometry::RECTANGLE, true));
    button->AddTag(action);
    menuLayer->AddGameObjectToLayer(button);
    return button;
}
