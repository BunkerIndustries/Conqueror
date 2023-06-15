#include "_Game.h"

#include "CreditLayer.h"

#include "renderer/Font.h"
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
	press = new GameObject("press ESC", Transform(glm::vec2(-0.7f, 0.85f), glm::vec2(0.05f, 0.05f)), ProjectionMode::SCREEN);
	press->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.9f, 0.7f, 1.0f), "Press ESC to\nreturn to menu", ui_font_family));
	press->AddTag("press");
	AddGameObjectToLayer(press);

	static float yOffset = 12.0f;
	angelina = new GameObject("credit1", Transform(glm::vec2(0.0f, 6.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	angelina->AddComponent(new FontRenderer(color, "Angelina Heller", ui_font_family));

	angelina_text = new GameObject("credit1", Transform(glm::vec2(0.0f, 5.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	angelina_text->AddComponent(new FontRenderer(color, "Grafikdesign", ui_font_family));

	levi = new GameObject("credit2", Transform(glm::vec2(0.0f, 3.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	levi->AddComponent(new FontRenderer(color, "Levi Laur", ui_font_family));

	levi_text = new GameObject("credit2", Transform(glm::vec2(0.0f, 2.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	levi_text->AddComponent(new FontRenderer(color, "Spiellogik Implementierung und Spielplanung", ui_font_family));

	matthias = new GameObject("credit3", Transform(glm::vec2(0.0f, 0.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	matthias->AddComponent(new FontRenderer(color, "Matthias Geng", ui_font_family));

	matthias_text = new GameObject("credit3", Transform(glm::vec2(0.0f, -1.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	matthias_text->AddComponent(new FontRenderer(color, "Grafikimplementierung, Animationen und Spielplanung", ui_font_family));

	pherel = new GameObject("credit4", Transform(glm::vec2(0.0f, -3.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	pherel->AddComponent(new FontRenderer(color, "Pherel Fazliu", ui_font_family));

	pherel_text = new GameObject("credit4", Transform(glm::vec2(0.0f, -4.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	pherel_text->AddComponent(new FontRenderer(color, "Engine Entwicklung und Engine Schnittstelle zum Spiel", ui_font_family));

	gutsche = new GameObject("credit5", Transform(glm::vec2(0.0f, -6.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	gutsche->AddComponent(new FontRenderer(color, "Pascal Gutsche", ui_font_family));

	gutsche_text = new GameObject("credit5", Transform(glm::vec2(0.0f, -7.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	gutsche_text->AddComponent(new FontRenderer(color, "Engine Entwicklung", ui_font_family));

	rahmen_des_seminarkurses = new GameObject("credit6", Transform(glm::vec2(0.0f, -10.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	rahmen_des_seminarkurses->AddComponent(new FontRenderer(color, "Im Rahmen des Seminarkurses:", ui_font_family));

	seminarkurs = new GameObject("credit7", Transform(glm::vec2(0.0f, -11.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	seminarkurs->AddComponent(new FontRenderer(color, "Erster Weltkrieg", ui_font_family));

	mentoren = new GameObject("credit8", Transform(glm::vec2(0.0f, -13.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	mentoren->AddComponent(new FontRenderer(color, "Mentoren:", ui_font_family));

	scn = new GameObject("credit9", Transform(glm::vec2(0.0f, -14.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	scn->AddComponent(new FontRenderer(color, "Nadja Schoenfeld", ui_font_family));

	lesle = new GameObject("credit10", Transform(glm::vec2(0.0f, -15.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	lesle->AddComponent(new FontRenderer(color, "Dr. phil. Steffen Lesle", ui_font_family));

	racic = new GameObject("credit11", Transform(glm::vec2(0.0f, -16.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	racic->AddComponent(new FontRenderer(color, "Alexander Racic", ui_font_family));

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
	AddGameObjectToLayer(rahmen_des_seminarkurses);
	AddGameObjectToLayer(seminarkurs);
	AddGameObjectToLayer(mentoren);
	AddGameObjectToLayer(scn);
	AddGameObjectToLayer(lesle);
	AddGameObjectToLayer(racic);

}

void CreditLayer::OnDetach()
{
	delete press;
	delete angelina;
	delete angelina_text;
	delete levi;
	delete levi_text;
	delete matthias;
	delete matthias_text;
	delete pherel;
	delete pherel_text;
	delete gutsche;
	delete gutsche_text;
	delete rahmen_des_seminarkurses;
	delete seminarkurs;
	delete mentoren;
	delete scn;
	delete lesle;
	delete racic;
	gameObjects.clear();
}


void CreditLayer::Update(const float dt)
{
	for (auto gm : gameObjects)
	{
		if (!gm->HasTag("press"))
			gm->transform.position.y += 1 * Application::GetDT();
	}

}

bool CreditLayer::KeyPressed(KeyPressedEvent& e)
{
	if (e.getKeyCode() == KEY_ESCAPE)
	{
		menuScene->CreditsStop();
		return true;
	}
	return false;
}

void CreditLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(CreditLayer::KeyPressed));
}


