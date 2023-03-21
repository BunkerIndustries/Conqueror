#include "_Game.h"

#include "AllyLayer.h"

AllyLayer::AllyLayer()
	: Layer("AllyLayer")
{

}

AllyLayer::~AllyLayer()
{
	for (auto i : gameObjects)
	{
		i->Delete();
	}
	gameObjects.clear();
}

void AllyLayer::OnAttach()
{

}

void AllyLayer::OnDetach()
{

}

void AllyLayer::Update(const float dt)
{

}

void AllyLayer::OnEvent(Event& event)
{

}
