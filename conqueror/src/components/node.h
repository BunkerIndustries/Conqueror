#pragma once
#include "Engine.h"

class Node : public Component {
public:
	Node(std::vector<GameObject*>* stand = nullptr);
	virtual ~Node() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	bool is_occupied;
	bool contains_soldier;

	std::vector<GameObject*>* stand;
};