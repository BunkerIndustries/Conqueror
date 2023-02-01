#include "ForegroundLayer.h"
#include <string>
#include <vector>

void ForegroundLayer::OnAttach()
{
	/*character1 = new GameObject("character1", Transform(glm::vec2(1.0f, -4.0f)));
	character2 = new GameObject("character2");
	object1 = new GameObject("object1", Transform(glm::vec2(-3, -4), glm::vec2(1.0f, 3.0f)));

	character1->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("IMG_0131.jpg"))));
	character2->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("antimarx.png"))));
	object1->addComponent(new SpriteRenderer(new Sprite(DataPool::getTexture("server-icon.png"))));

	this->AddGameObjectToLayer(character1);
	this->AddGameObjectToLayer(character2);
	this->AddGameObjectToLayer(object1);*/

	CreateGrid(3);
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

void ForegroundLayer::CreateGrid(int x_size) {
	std::vector<GameObject*> grid_vec;
	for (size_t i = 0; i < x_size; i++) {
		grid_vec.push_back(new GameObject(std::to_string(i), Transform(glm::vec2(i * 2.0f, 0.0f), glm::vec2(0.2f, 0.2f))));
		grid_vec.at(i)->addComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
		this->AddGameObjectToLayer(grid_vec.at(i));
	}
}

void ForegroundLayer::imgui(const float dt)
{
}

void ForegroundLayer::OnEvent(Event& event)
{
}
