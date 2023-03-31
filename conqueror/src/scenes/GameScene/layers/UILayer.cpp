#include "_Game.h"

#include "UILayer.h"

UILayer::UILayer()
	: Layer("UILayer")
{
}

UILayer::~UILayer()
{
}

void UILayer::OnAttach()
{
}

void UILayer::OnDetach()
{
}

void UILayer::Update(const float dt)
{
}

bool UILayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	//if (e.GetGameObject()->HasTag("UI"))
	//	OnUIClick()
	return false;
}

void UILayer::OnUIClick()
{
}

void UILayer::OnGOClick(GameObject* gameObject)
{
}

void UILayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(UILayer::OnGameObjectClick));
}


