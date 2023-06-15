#include "_Game.h"

#include "MenuLayer.h"

#include "required/constants.h"

Shr<Sound> MenuLayer::menu_theme;

MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{

}

void MenuLayer::Init()
{
	menu_theme = MakeShr<Sound>();

	menu_theme->LoadSound("assets/sounds/menud.wav");
}

void MenuLayer::OnAttach()
{
}

void MenuLayer::OnDetach()
{
	menu_theme->StopSound();
}

void MenuLayer::Update(const float dt)
{
	menu_theme->SoundPlay();
}

bool MenuLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	GameObject* go = e.GetGameObject();

	if (go->HasTag("play")) {
		Util::menu_select->SoundPlay();
		delete gameScene;
		gameScene = new GameScene();
		Application::ChangeScene(gameScene);
	}
	else if (go->HasTag("resume"))
	{
		Application::ChangeScene(gameScene);
	}
	else if (go->HasTag("credit"))
	{
		menuScene->CreditsStart();
	}
	else if (go->HasTag("quit")) 
	{
		Application::GetInstance()->Exit();
	}

	return true;
}

void MenuLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(MenuLayer::OnGameObjectClick));
}

void MenuLayer::ResetButton()
{
	delete gameScene;
	gameScene = nullptr;
	Application::ChangeScene(new MenuScene(), true);
}


