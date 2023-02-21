#pragma once
#include "Engine.h"

class Node : public Component {
public:
	Node();
	virtual ~Node() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	bool is_occupied;
};