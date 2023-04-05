#include "_Game.h"

#include "MenuLayer.h"

#include "required/constants.h"

MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}

void MenuLayer::OnAttach()
{
}

void MenuLayer::OnDetach()
{
}

void MenuLayer::Update(const float dt)
{
}

bool MenuLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
    GameObject* go = e.GetGameObject();

    if (go->HasTag("play")) {
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


