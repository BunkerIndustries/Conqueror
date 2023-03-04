#pragma once
#include "Engine.h"

class SoldierBehaviour : public Component {
public:
	SoldierBehaviour();
	virtual ~SoldierBehaviour() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void SoldierMove(GameObject* node);

private:
	bool can_shoot;
	bool travelling;

	float dt_counter;
	float time_to_wait;

	std::vector<GameObject*>* stand;
};