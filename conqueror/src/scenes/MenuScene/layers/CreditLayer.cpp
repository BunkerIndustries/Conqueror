#include "_Game.h"

#include "CreditLayer.h"

#include "required/constants.h"

CreditLayer::CreditLayer()
{
}

CreditLayer::~CreditLayer()
{
}

void CreditLayer::OnAttach()
{

}

void CreditLayer::OnDetach()
{

}

void CreditLayer::Update(const float dt)
{

}

bool CreditLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	GameObject* go = e.GetGameObject();
	if (go->HasTag("play")) {
		delete gameScene;
		gameScene = new GameScene();
		Application::ChangeScene(gameScene);
	}
	else if (go->HasTag("resume"))
	{
		Application::ChangeScene(gameScene);
	}
	else if (go->HasTag("quit")) {
		Application::GetInstance()->Exit();
	}
	
	return true;
}

void CreditLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	//dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(MenuLayer::OnGameObjectClick));
}


