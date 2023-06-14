#pragma once
#include "_Game.h"
#include "layer/Layer.h"

class StatLayer : public Layer {
public:
	StatLayer();
	~StatLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;

private: 
	bool OnGameObjectClick(GameObjectPressedEvent& e);
};