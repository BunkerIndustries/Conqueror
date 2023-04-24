#pragma once
#include "layer/Layer.h"
#include "_Game.h"

class BackgroundLayer : public Layer
{
public:

	BackgroundLayer();
	~BackgroundLayer() override = default;

	void OnAttach() override;
	void OnDetach() override {};
	void Update(const float dt) override {};
	void OnEvent(Event& e) override {};

private:
	void CreateBackgroundTile(glm::vec2 pos);
};