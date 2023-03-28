#pragma once
#include "Engine.h"

class EngineerBehaviour : public Component {
public:
	EngineerBehaviour(GameObject* building_node);
	virtual ~MedicBehaviour() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	GameObject* building_Node;
	glm::vec2 building_node_position;

	bool building;
	bool going_back;
	float build_time;
	float dt_counter;
};
