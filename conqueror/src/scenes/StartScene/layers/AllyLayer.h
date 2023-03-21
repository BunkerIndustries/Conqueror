#pragma once
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
};