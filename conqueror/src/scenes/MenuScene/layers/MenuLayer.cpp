#include "_Game.h"

#include "MenuLayer.h"

#include "required/constants.h"

Shr<Sound> MenuLayer::menu_theme;
Shr<Sound> MenuLayer::menu_select;

MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}

void MenuLayer::Init()
{
	menu_theme = MakeShr<Sound>();
	menu_select = MakeShr<Sound>();
	menu_theme->LoadSound("assets/sounds/menud.wav");
	menu_select->LoadSound("assets/sounds/start.wav");
}

void MenuLayer::OnAttach()
{
	menu_theme->SoundPlay();
}

void MenuLayer::OnDetach()
{
	menu_theme->StopSound();
}

void MenuLayer::Update(const float dt)
{
}

bool MenuLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	GameObject* go = e.GetGameObject();

	if (go->HasTag("play")) {
		delete gameScene;
		menu_select->SoundPlay();
		gameScene = new GameScene();
		Application::ChangeScene(gameScene);
	}
	else if (go->HasTag("quit")) {
		Application::GetInstance()->Exit();
	}

	return true;
}

void MenuLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(MenuLayer::OnGameObjectClick));
}


