#pragma once
#include "Engine.h"

class Movement : public Component {
public:
	Movement();
	virtual ~Movement();

	void start() override;
	void stop() override;
	void update(float ddt) override;
	void event(Event& event) override;
};