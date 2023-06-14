#pragma once
#include "layer/Layer.h"
#include "_Game.h"

class MenuBackgroundLayer : public Layer
{
public:

	MenuBackgroundLayer();
	~MenuBackgroundLayer() override = default;

	void OnAttach() override;
	void OnDetach() override{};
	void Update(const float dt) override {};
	void OnEvent(Event& e) override {};

private:
	void CreateBackgroundTile(glm::vec2 pos);
};