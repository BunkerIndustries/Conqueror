#pragma once
#include "_Game.h"
#include "layer/Layer.h"

class AllyLayer : public Layer
{
public:

	AllyLayer();
	~AllyLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(AllyLayer::KeyReleased));
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(AllyLayer::GameObjectPressed));
	};
	bool KeyReleased(KeyReleasedEvent& e);
	bool GameObjectPressed(GameObjectPressedEvent& e);

	GameObject* CreateCharacter(std::string type, Transform transform);
	GameObject* AllyLayer::CreateMg(glm::vec2 mg_node_position);

private:
};