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
	Panel* p = new Panel(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Transform(glm::vec2(0.0f, 1.0f), glm::vec2(2.0f, 2.0f)), Type::Rectangle);
	Button* b = new Button(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), Transform(glm::vec2(0.0f, -0.5f), glm::vec2(1.0f, 1.0f)), Type::Rectangle, BIND_BUTTON_EVENT_FN(UILayer::test));
	p->AddChildObject(b);
	Label* l = new Label("test", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Transform(glm::vec2(0.0f, 0.5f), glm::vec2(1.0f, 1.0f)));
	p->AddChildObject(l);

	AddUIObject(p, ProjectionMode::PERSPECTIVE);

}

void UILayer::test() {

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


