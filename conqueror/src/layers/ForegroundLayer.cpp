#include "_Game.h"
#include "ForegroundLayer.h"

void ForegroundLayer::OnAttach()
{
}

void ForegroundLayer::OnDetach()
{
	for (auto i : gameObjects)
	{
		delete i;
	}
	gameObjects.clear();
}

void ForegroundLayer::Update(const float dt)
{
}

void ForegroundLayer::Imgui(const float dt)
{
}

void ForegroundLayer::OnEvent(Event& event)
{
}
