#pragma once
#include "Engine.h"

class MedicBehaviour : public Component {
public:
	MedicBehaviour(GameObject* healing_target);
	virtual ~MedicBehaviour() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	GameObject* healing_target;
	glm::vec2 healing_target_position;

	bool healing;
	bool going_back;
	float heal_time;
	float dt_counter;
};
