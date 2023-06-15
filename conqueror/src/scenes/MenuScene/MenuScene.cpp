#include "_Game.h"

#include "MenuScene.h"
#include "../GameScene/GameScene.h"

Shr<Sound> MenuScene::sound_credit;

void MenuScene::Init()
{
	sound_credit = MakeShr<Sound>();
	sound_credit->LoadSound("assets/sounds/credits.wav");
}

MenuScene::MenuScene() {
	backcolor = background_color;

	menuLayer = new MenuLayer();
	menuBackgroundLayer = new MenuBackgroundLayer();
	creditLayer = new CreditLayer();

	CreateElement("title_object_001.png", glm::vec2(0.0f, 3.0f), glm::vec2(11.0f, 3.0f));
	if (gameScene)
	{
		CreateButton("resume_object_001.png", glm::vec2(0.0f, 0.0f), "resume");
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
	sound_credit->SoundPlay();

	creditLayer->Attach();
}

void MenuScene::CreditsStop()
{
	creditLayer->Detach();

	menuLayer->Attach();
	
	sound_credit->StopSound();
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
