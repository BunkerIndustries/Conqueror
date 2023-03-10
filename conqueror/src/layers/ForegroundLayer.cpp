#include "ForegroundLayer.h"
#include <string>
#include <vector>

void ForegroundLayer::OnAttach()
{
}

void ForegroundLayer::OnDetach()
{
	for (auto i : game_objects)
	{
		i->Delete();
	}
	game_objects.clear();
}

void ForegroundLayer::update(const float dt)
{
}

void ForegroundLayer::imgui(const float dt)
{
}

void ForegroundLayer::OnEvent(Event& event)
{
}
