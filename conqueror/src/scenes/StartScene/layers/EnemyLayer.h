#pragma once
#include "layer/Layer.h"

class EnemyLayer : public Layer
{
public:

	EnemyLayer();
	~EnemyLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;
};