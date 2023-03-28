#pragma once
#include "Engine.h"

class EngineerManagement : public Component {
public:
	EngineerManagement(uint8_t number_of_engineers);
	virtual ~EngineerManagement() = default;

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};

private:
	uint8_t available_engineers;
};