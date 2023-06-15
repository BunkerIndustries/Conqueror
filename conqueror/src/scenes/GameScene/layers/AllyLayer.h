#pragma once
#include "_Game.h"
#include "layer/Layer.h"

struct Stand;

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

	GameObject* CreateSoldier(glm::vec2 position);
	GameObject* CreateMedic(glm::vec2 position);
	GameObject* CreateEngineer(glm::vec2 position, bool mg_artillery);

	static void Init();

	static Shr<Sound> soldier_click;
	static Shr<Sound> medic_click;
	static Shr<Sound> engineer_click;
private:
};