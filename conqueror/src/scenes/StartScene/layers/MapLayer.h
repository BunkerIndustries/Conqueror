#pragma once
#include "layer/Layer.h"

class MapLayer : public Layer
{
public:

	MapLayer();
	~MapLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;
};