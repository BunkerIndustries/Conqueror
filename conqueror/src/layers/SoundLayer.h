#pragma once
#include "Engine.h"

class SoundLayer : public Layer
{
private:
	Sound soundSel;
	Sound soundTroll;
	float volume = 1.0f;

public:
	SoundLayer()
		:Layer("Sound") { }
	virtual ~SoundLayer() = default;

	void OnAttach() override;
	void OnDetach() override;
	void update(const float dt) override;
	void imgui(const float dt) override;
	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(SoundLayer::OnKeyPressed));
	}

	bool OnKeyPressed(KeyPressedEvent& e);

};

