#pragma once
#include "Engine.h"

class DestroyOverTime : public Component {
public:
	DestroyOverTime() = default;
	virtual ~DestroyOverTime() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	float dt_counter = 0.0f;
	float time;
};