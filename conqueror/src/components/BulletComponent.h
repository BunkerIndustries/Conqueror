#pragma once
#include "_Game.h"

class BulletComponent : public Component
{
public:
	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override;

private:

};

