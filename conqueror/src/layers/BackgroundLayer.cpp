#include "BackgroundLayer.h"

void BackgroundLayer::OnAttach()
{
    /*background1 = new GameObject("Background", Transform(glm::vec2(-3.0f, 2.0f), glm::vec2(2.0f, 2.0f)));
    background2 = new GameObject("Background", Transform(glm::vec2(0.0f, 2.0f), glm::vec2(2.0f, 2.0f)));
    background3 = new GameObject("Background", Transform(glm::vec2(3.0f, 2.0f), glm::vec2(2.0f, 2.0f)));
    background4 = new GameObject("Background", Transform(glm::vec2(-3.0f, -1.0f), glm::vec2(2.0f, 2.0f)));
    background5 = new GameObject("Background", Transform(glm::vec2(3.0f, -1.0f), glm::vec2(2.0f, 2.0f)));
    background6 = new GameObject("Background", Transform(glm::vec2(-3.0f, -4.0f), glm::vec2(2.0f, 2.0f)));
    background7 = new GameObject("Background", Transform(glm::vec2(0.0f, -4.0f), glm::vec2(2.0f, 2.0f)));
    background8 = new GameObject("Background", Transform(glm::vec2(3.0f, -4.0f), glm::vec2(2.0f, 2.0f)));
    
    background1->AddTag("background");
    
    background1->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
    background2->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
    background3->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    background4->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)));
    background5->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
    background6->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
    background7->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
    background8->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    
    
    this->AddGameObjectToLayer(background1);
    this->AddGameObjectToLayer(background2);
    this->AddGameObjectToLayer(background3);
    this->AddGameObjectToLayer(background4);
    this->AddGameObjectToLayer(background5);
    this->AddGameObjectToLayer(background6);
    this->AddGameObjectToLayer(background7);
    this->AddGameObjectToLayer(background8);*/
}

void BackgroundLayer::OnDetach()
{
    /*for (auto i : game_objects)
    {
        delete i;
    }
    game_objects.clear();*/

}

void BackgroundLayer::update(const float dt)
{
}

void BackgroundLayer::imgui(const float dt)
{
}

void BackgroundLayer::OnEvent(Event& event)
{
}
