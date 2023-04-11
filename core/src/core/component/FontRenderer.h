#pragma once
#include "generic/Component.h"

namespace core
{
	class FontRenderer : public Component
	{
	public:
		FontRenderer(glm::vec4 color, std::string text, std::string fontPath = "assets/fonts/mononoki.ttf");

		void ChangeText(std::string text);

		void OnStart() override { }
		void OnStop() override { }
		void OnUpdate() override;
		void OnEvent(Event& event) override { }

	private:
		glm::vec4 color;
		std::string text;
		std::string fontPath;

	};
};


