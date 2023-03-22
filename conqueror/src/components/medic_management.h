#pragma once
#include "Engine.h"

class MedicManagement : public Component {
public:
	MedicManagement(uint8_t number_of_medics);
	virtual ~MedicManagement() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

	void SendMedic(GameObject* healing_target);
	void MedicArrived();

private:
	uint8_t available_medics;
};