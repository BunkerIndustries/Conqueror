#include "_Game.h"

#include "StatLayer.h"
#include "required/constants.h"
#include "Scenes/GameOverScene/GameOverScene.h"

StatLayer::StatLayer()
	: Layer("StatLayer")
{
}

StatLayer::~StatLayer() {

}

void StatLayer::OnAttach() {

}

void StatLayer::OnDetach() {

}

void StatLayer::Update(const float dt) {

}

bool StatLayer::OnGameObjectClick(GameObjectPressedEvent& e) {
	GameObject* go = e.GetGameObject();

	if (go->HasTag("menu")) {
		delete menuScene;
		menuScene = new MenuScene();
		Application::ChangeScene(menuScene);
	}
	return true;
}

void StatLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(StatLayer::OnGameObjectClick));
}

