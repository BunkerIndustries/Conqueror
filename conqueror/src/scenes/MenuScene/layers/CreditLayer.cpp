#include "_Game.h"

#include "CreditLayer.h"

#include "required/constants.h"

CreditLayer::CreditLayer()
{

}

CreditLayer::~CreditLayer()
{

}

void CreditLayer::OnAttach()
{
	angelina = new GameObject("credit1");
	angelina->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.1f, 0.2f, 1.0f), "Angelina Heller\nGrafikdesign"));
	AddGameObjectToLayer(angelina);

	levi = new GameObject("credit2");
	levi->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.1f, 0.2f, 1.0f), "Levi Lauer\nSpieldesign und Spielplanung"));
	AddGameObjectToLayer(levi);

	matthias = new GameObject("credit3");
	matthias->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.1f, 0.2f, 1.0f), "Matthias Geng\nGrafikimplementierung, Animationen und Spielplanung"));
	AddGameObjectToLayer(matthias);

	pherel = new GameObject("credit4");
	pherel->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.1f, 0.2f, 1.0f), "Pherel Fazliu\nEngine Entwicklung"));
	AddGameObjectToLayer(pherel);

	gutsche = new GameObject("credit5");
	gutsche->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.1f, 0.2f, 1.0f), "Pascal Gutsche\nEngine Entwicklung"));
	AddGameObjectToLayer(gutsche);

}

void CreditLayer::OnDetach()
{

}

void CreditLayer::Update(const float dt)
{

}

bool CreditLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	
}

void CreditLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
}


