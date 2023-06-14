#include "_Game.h"

#include "CreditLayer.h"

#include "required/constants.h"

CreditLayer::CreditLayer()
{

}

CreditLayer::~CreditLayer()
{

}
static glm::vec4 color = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
void CreditLayer::OnAttach()
{
	angelina = new GameObject("credit1", Transform(glm::vec2(0.0f, 6.0f), glm::vec2(0.5f, 0.5f)));
	angelina->AddComponent(new FontRenderer(color, "Angelina Heller", ui_font_family));

	angelina_text = new GameObject("credit1", Transform(glm::vec2(0.0f, 5.0f), glm::vec2(0.5f, 0.5f)));
	angelina_text->AddComponent(new FontRenderer(color, "Grafikdesign", ui_font_family));

	levi = new GameObject("credit2", Transform(glm::vec2(0.0f, 3.0f), glm::vec2(0.5f, 0.5f)));
	levi->AddComponent(new FontRenderer(color, "Levi Lauer", ui_font_family));

	levi_text = new GameObject("credit2", Transform(glm::vec2(0.0f, 3.0f), glm::vec2(0.5f, 0.5f)));
	levi_text->AddComponent(new FontRenderer(color, "Spieldesign und Spielplanung", ui_font_family));

	matthias = new GameObject("credit3", Transform(glm::vec2(0.0f, 1.0f), glm::vec2(0.5f, 0.5f)));
	matthias->AddComponent(new FontRenderer(color, "Matthias Geng", ui_font_family));

	matthias_text = new GameObject("credit3", Transform(glm::vec2(0.0f, 1.0f), glm::vec2(0.5f, 0.5f)));
	matthias_text->AddComponent(new FontRenderer(color, "Grafikimplementierung, Animationen und Spielplanung", ui_font_family));

	pherel = new GameObject("credit4", Transform(glm::vec2(0.0f, -1.0f), glm::vec2(0.5f, 0.5f)));
	pherel->AddComponent(new FontRenderer(color, "Pherel Fazliu", ui_font_family));

	pherel_text = new GameObject("credit4", Transform(glm::vec2(0.0f, -1.0f), glm::vec2(0.5f, 0.5f)));
	pherel_text->AddComponent(new FontRenderer(color, "Engine Entwicklung", ui_font_family));

	gutsche = new GameObject("credit5", Transform(glm::vec2(0.0f, -3.0f), glm::vec2(0.5f, 0.5f)));
	gutsche->AddComponent(new FontRenderer(color, "Pascal Gutsche", ui_font_family));

	gutsche_text = new GameObject("credit5", Transform(glm::vec2(0.0f, -3.0f), glm::vec2(0.5f, 0.5f)));
	gutsche_text->AddComponent(new FontRenderer(color, "Engine Entwicklung", ui_font_family));


	AddGameObjectToLayer(angelina);
	AddGameObjectToLayer(angelina_text);
	AddGameObjectToLayer(levi);
	AddGameObjectToLayer(levi_text);
	AddGameObjectToLayer(matthias);
	AddGameObjectToLayer(matthias_text);
	AddGameObjectToLayer(pherel);
	AddGameObjectToLayer(pherel_text);
	AddGameObjectToLayer(gutsche);
	AddGameObjectToLayer(gutsche_text);

}

void CreditLayer::OnDetach()
{

}

void CreditLayer::Update(const float dt)
{

}

bool CreditLayer::OnGameObjectClick(GameObjectPressedEvent& e)
{
	return false;
}

void CreditLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
}


