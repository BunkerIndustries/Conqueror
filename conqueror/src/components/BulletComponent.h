#pragma once
#include "_Game.h"

class BulletComponent : public Component
{
public:
	BulletComponent(GameObject* target, glm::vec2 pos);

	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override;

	static void Init();
	static Shr<Sound> sound_mg;

private:
	GameObject* target;
	glm::vec2 pos;
};

