#include "ForegroundLayer.h"


void ForegroundLayer::OnAttach()
{
	character1 = new GameObject("character1", Transform(glm::vec2(1.0f, -4.0f)));
	character2 = new GameObject("character2");
	object1 = new GameObject("object1", Transform(glm::vec2(-3, -4), glm::vec2(1.0f, 3.0f)));

	character1->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("IMG_0131.jpg"))));
	character2->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("antimarx.png"))));
	object1->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("server-icon.png"))));

	this->AddGameObjectToLayer(character1);
	this->AddGameObjectToLayer(character2);
	this->AddGameObjectToLayer(object1);
}

void ForegroundLayer::OnDetach()
{
	for (auto i : game_objects)
	{
		delete i;
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
