#include "ForegroundLayer.h"
#include <string>
#include <vector>

void ForegroundLayer::OnAttach()
{
	//GameObject* character1 = new GameObject("character1", Transform(glm::vec2(0.0f, 0.0f)));
	//GameObject* character2 = new GameObject("character2", Transform(glm::vec2(2.0f, 0.0f)));
	/*GameObject *character2 = new GameObject("character2");
	GameObject *object1 = new GameObject("object1", Transform(glm::vec2(-3, -4), glm::vec2(1.0f, 3.0f)));*/

	//character1->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("IMG_0131.jpg"))));
	//character2->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("antimarx.png"))));
	/*character2->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("antimarx.png"))));
	object1->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("server-icon.png"))));*/

	//this->AddGameObjectToLayer(character1);
	//this->AddGameObjectToLayer(character2);
	/*this->AddGameObjectToLayer(character2);
	this->AddGameObjectToLayer(object1);*/


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

	/*if (Input::IsKeyPressed(KEY_D)) {
		test_go->transform.position.x += speed * dt;
	}
	if (Input::IsKeyPressed(KEY_A)) {
		test_go->transform.position.x -= speed * dt;
	}
	if (Input::IsKeyPressed(KEY_W)) {
		test_go->transform.position.y += speed * dt;
	}
	if (Input::IsKeyPressed(KEY_S)) {
		test_go->transform.position.y -= speed * dt;
	}

	if (Input::IsKeyPressed(KEY_DOWN)) {
		test_go->transform.scale.x += 1.0f * dt;
		test_go->transform.scale.y += 1.0f * dt;
	}
	if (Input::IsKeyPressed(KEY_UP)) {
		test_go->transform.scale.x -= 1.0f * dt;
		test_go->transform.scale.y -= 1.0f * dt;
	}*/

}

void ForegroundLayer::imgui(const float dt)
{
}

void ForegroundLayer::OnEvent(Event& event)
{
}
