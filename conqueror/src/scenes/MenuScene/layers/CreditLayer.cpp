#include "_Game.h"

#include "CreditLayer.h"

#include "renderer/Font.h"
#include "required/constants.h"

Shr<Sound> CreditLayer::sound_credit;

void CreditLayer::Init()
{
	sound_credit = MakeShr<Sound>();
	sound_credit->LoadSound("assets/sounds/credits.wav");
}


CreditLayer::CreditLayer()
{

} 

CreditLayer::~CreditLayer()
{

}
static glm::vec4 color = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
static glm::vec4 name_color = glm::vec4(0.75f, 0.75f, 1.0f, 1.0f);
void CreditLayer::OnAttach()
{
	press = new GameObject("press ESC", Transform(glm::vec2(-0.7f, 0.85f), glm::vec2(0.05f, 0.05f)), ProjectionMode::SCREEN);
	press->AddComponent(new FontRenderer(glm::vec4(0.8f, 0.9f, 0.7f, 1.0f), "Press ESC to\nreturn to menu", ui_font_family));
	press->AddTag("press");
	AddGameObjectToLayer(press);

	static float yOffset = 7.0f;
	angelina = new GameObject("credit1", Transform(glm::vec2(0.0f, 0.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	angelina->AddComponent(new FontRenderer(name_color, "Angelina Heller", ui_font_family));

	angelina_text = new GameObject("credit1", Transform(glm::vec2(0.0f, -1.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	angelina_text->AddComponent(new FontRenderer(color, "Grafikdesign", ui_font_family));

	levi = new GameObject("credit2", Transform(glm::vec2(0.0f, -3.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	levi->AddComponent(new FontRenderer(name_color, "Levi Laur", ui_font_family));

	levi_text = new GameObject("credit2", Transform(glm::vec2(0.0f, -4.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	levi_text->AddComponent(new FontRenderer(color, "Spielentwicklung und Spielplanung", ui_font_family));

	matthias = new GameObject("credit3", Transform(glm::vec2(0.0f, -6.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	matthias->AddComponent(new FontRenderer(name_color, "Matthias Geng", ui_font_family));

	matthias_text = new GameObject("credit3", Transform(glm::vec2(0.0f, -7.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	matthias_text->AddComponent(new FontRenderer(color, "Grafikimplementierung, Animationen und Spielplanung", ui_font_family));

	pherel = new GameObject("credit4", Transform(glm::vec2(0.0f, -9.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	pherel->AddComponent(new FontRenderer(name_color, "Pherel Fazliu", ui_font_family));

	pherel_text = new GameObject("credit4", Transform(glm::vec2(0.0f, -10.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	pherel_text->AddComponent(new FontRenderer(color, "Engine Entwicklung und Sound", ui_font_family));

	gutsche = new GameObject("credit5", Transform(glm::vec2(0.0f, -12.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	gutsche->AddComponent(new FontRenderer(name_color, "Pascal Gutsche", ui_font_family));

	gutsche_text = new GameObject("credit5", Transform(glm::vec2(0.0f, -13.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	gutsche_text->AddComponent(new FontRenderer(color, "Engine Entwicklung und bug fixing", ui_font_family));

	rahmen_des_seminarkurses = new GameObject("credit6", Transform(glm::vec2(0.0f, -16.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	rahmen_des_seminarkurses->AddComponent(new FontRenderer(name_color, "Im Rahmen des Seminarkurses:", ui_font_family));

	seminarkurs = new GameObject("credit7", Transform(glm::vec2(0.0f, -17.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	seminarkurs->AddComponent(new FontRenderer(color, "Erster Weltkrieg", ui_font_family));

	mentoren = new GameObject("credit8", Transform(glm::vec2(0.0f, -19.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	mentoren->AddComponent(new FontRenderer(name_color, "Mentoren:", ui_font_family));

	scn = new GameObject("credit9", Transform(glm::vec2(0.0f, -20.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	scn->AddComponent(new FontRenderer(color, "Nadja Schoenfeld", ui_font_family));

	lesle = new GameObject("credit10", Transform(glm::vec2(0.0f, -21.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	lesle->AddComponent(new FontRenderer(color, "Dr. phil. Steffen Lesle", ui_font_family));

	racic = new GameObject("credit11", Transform(glm::vec2(0.0f, -22.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	racic->AddComponent(new FontRenderer(color, "Alexander Racic", ui_font_family));

	special_thanks = new GameObject("credit12", Transform(glm::vec2(0.0f, -24.0f - yOffset), glm::vec2(0.7f, 0.7f)));
	special_thanks->AddComponent(new FontRenderer(name_color, "Special Thanks:", ui_font_family));

	boris = new GameObject("credit13", Transform(glm::vec2(0.0f, -25.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	boris->AddComponent(new FontRenderer(color, "Boris_HET", ui_font_family));

	nam = new GameObject("credit14", Transform(glm::vec2(0.0f, -26.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	nam->AddComponent(new FontRenderer(color, "Hoai Nam Nguyen", ui_font_family));

	racic2 = new GameObject("credit15", Transform(glm::vec2(0.0f, -27.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	racic2->AddComponent(new FontRenderer(color, "Alexander Racic", ui_font_family));

	rebstock = new GameObject("credit16", Transform(glm::vec2(0.0f, -28.0f - yOffset), glm::vec2(0.5f, 0.5f)));
	rebstock->AddComponent(new FontRenderer(color, "Heiko Rebstock", ui_font_family));

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
	AddGameObjectToLayer(special_thanks);
	AddGameObjectToLayer(boris);
	AddGameObjectToLayer(nam);
	AddGameObjectToLayer(racic2);
	AddGameObjectToLayer(rebstock);

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

	sound_credit->StopSound();

}


void CreditLayer::Update(const float dt)
{
	static float posY = 0;
	sound_credit->SoundPlay();
	for (auto gm : gameObjects)
	{
		if (!gm->HasTag("press"))
		{
			gm->transform.position.y += 1 * Application::GetDT();
		}
	}
	posY += 1 * Application::GetDT();
	if (posY >= 41.0f)
	{
		for (auto gm : gameObjects)
		{
			if (!gm->HasTag("press"))
				gm->transform.position.y -= posY;
		}
		posY = 0.0f;
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


