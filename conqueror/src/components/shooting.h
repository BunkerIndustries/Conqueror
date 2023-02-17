#pragma once
#include "Engine.h"

class Shooting : public Component {
public:
	Shooting();
	virtual ~Shooting() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

};