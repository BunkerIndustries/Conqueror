#include "_Game.h"

#include "StatLayer.h"

#include "required/constants.h"

StatLayer::StatLayer()
{
}

StatLayer::~StatLayer()
{
}

void StatLayer::OnAttach()
{
	Label* title = new Label("GAME OVER!", glm::vec4(1.0f, 0.4f, 0.4f, 0.9f), Transform(glm::vec2(0.0f, 0.5f), glm::vec2(0.1f, 0.18f)), DataPool::GetFont(ui_font_family));
	Label* text = new Label(("Du hast " + std::to_string(waves_survived) + " Wellen standgehalten"), white_color, Transform(glm::vec2(0.0f, 0.25f), glm::vec2(0.05f, 0.1f)), DataPool::GetFont(ui_font_family));
	AddUIObject(title, ProjectionMode::SCREEN); AddUIObject(text, ProjectionMode::SCREEN);
}

void StatLayer::OnDetach()
{
}

void StatLayer::Update(const float dt)
{
}

bool StatLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	GameObject* go = e.GetGameObject();

	if (go->HasTag("play")) {
		delete gameScene;
		gameScene = new GameScene();
		Application::ChangeScene(gameScene);
	}
	else if (go->HasTag("main-menu")) {
		Application::ChangeScene(menuScene);
	}

	return true;
}

void StatLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(StatLayer::OnGameObjectClick));
}


