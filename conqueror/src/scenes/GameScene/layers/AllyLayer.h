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
	void OnEvent(Event& event) override;

	GameObject* CreateCharacter(std::string type, Transform transform);
	GameObject* AllyLayer::CreateMg(glm::vec2 mg_node_position);

private:
};