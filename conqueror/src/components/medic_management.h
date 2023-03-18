#pragma once
#include "Engine.h"
#include <vector>

class MedicManagement : public Component {
public:
	MedicManagement(uint8_t number_of_medics);
	virtual ~MedicManagement() = default;

	void start() override;
	void stop() override;
	void update(float dt) override;
	void event(Event& event) override {};

	void SendMedic(GameObject* healing_target);
	void MedicArrived();

private:
	uint8_t available_medics;
};