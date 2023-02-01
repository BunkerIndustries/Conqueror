#pragma once
#include "Engine.h"
class ForegroundLayer : public Layer
{
private:
	/*GameObject* character1;
	GameObject* character2;
	GameObject* object1;*/

	GameObject* test_go;

	//int speed = 2;

public:
	ForegroundLayer(): Layer("Foreground") { }
	virtual ~ForegroundLayer() = default;

	void OnAttach() override;
	void OnDetach() override;
	void update(const float dt) override;
	void imgui(const float dt) override;
	void OnEvent(Event& event) override;

	void CreateGrid(int);
};

