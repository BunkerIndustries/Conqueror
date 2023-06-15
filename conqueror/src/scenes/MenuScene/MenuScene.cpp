#include "_Game.h"

#include "MenuScene.h"
#include "../GameScene/GameScene.h"


MenuScene::MenuScene() {
	menuScene = this;
	backcolor = background_color;

	menuLayer = new MenuLayer();
	menuBackgroundLayer = new MenuBackgroundLayer();
	creditLayer = new CreditLayer();

	CreateElement("title_object_001.png", glm::vec2(0.0f, 3.0f), glm::vec2(11.0f, 3.0f));
	if (gameScene)
	{
		CreateButton("resume_object_001.png", glm::vec2(0.0f, 0.0f), "resume");
		CreateResetButton(glm::vec2(7.0f, 0.0f));
	}
	else
	{
		CreateButton("play_object_001.png", glm::vec2(0.0f, 0.0f), "play");
	}
	CreateButton("credits_object_001.png", glm::vec2(0.0f, -2.0f), "credit");
	CreateButton("quit_button.png", glm::vec2(0.0f, -4.0f), "quit");
}
 
MenuScene::~MenuScene() {

}

void MenuScene::OnStart() {
	AddLayer(menuBackgroundLayer);
	AddLayer(menuLayer);
	AddLayer(creditLayer);
	creditLayer->Detach();
}

void MenuScene::OnStop() {
	RemoveLayer(menuBackgroundLayer);
	RemoveLayer(menuLayer);
	RemoveLayer(creditLayer);
}

void MenuScene::OnUpdate() {

}

void MenuScene::CreditsStart()
{
	menuLayer->Detach();

	creditLayer->Attach();
}

void MenuScene::CreditsStop()
{
	creditLayer->Detach();

	menuLayer->Attach();
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

GameObject* MenuScene::CreateResetButton(glm::vec2 position) {
	Button* button = new Button(glm::vec4(0.0f, 0.0f, 0.0f, 0.01f), Transform(position, glm::vec2(4.0f, 1.7f)), Type::Rectangle, MenuLayer::ResetButton);
	Label* label = new Label("RESET", white_color, Transform(glm::vec2(0.0f), glm::vec2(0.25f, 1.0f)), DataPool::GetFont(ui_font_family));
	button->AddChildObject(label);
	menuScene->menuLayer->AddUIObject(button, ProjectionMode::PERSPECTIVE);
	return nullptr;
}
