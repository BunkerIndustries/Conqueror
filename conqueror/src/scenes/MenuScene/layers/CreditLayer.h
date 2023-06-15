#pragma once
#include "layer/Layer.h"

class CreditLayer : public Layer
{
public:

	CreditLayer();
	~CreditLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& event) override;

	static void Init();

	static Shr<Sound> sound_credit;

private:
	bool KeyPressed(KeyPressedEvent& e);

	GameObject* press;

	GameObject* angelina;
	GameObject* angelina_text;

	GameObject* levi;
	GameObject* levi_text;

	GameObject* matthias;
	GameObject* matthias_text;

	GameObject* pherel;
	GameObject* pherel_text;

	GameObject* gutsche;
	GameObject* gutsche_text;

	GameObject* rahmen_des_seminarkurses;
	GameObject* seminarkurs;
	GameObject* mentoren;
	GameObject* scn;
	GameObject* lesle;
	GameObject* racic;

};