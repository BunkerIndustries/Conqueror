#pragma once
#include "Engine.h"

class ArtilleryComponent : public Component {
public:
	ArtilleryComponent(GameObject* own_node);
	virtual ~ArtilleryComponent() = default;

	static void Init();
	void OnStart() override;
	void OnStop() override;
	void OnUpdate() override;
	void OnEvent(Event& event) override {};
	
	static Shr<Sound> shoot_sound;

private:
	float dt_counter;
	float reload_time;
	Node* own_node;

	void Shoot();
};