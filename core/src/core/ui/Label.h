#pragma once
#include "_Core.h"

#include "UIObject.h"

namespace core
{
	class Label : public UIObject
	{
	public:
		Label(std::string text, glm::vec4 color, const Transform& transform, std::string name = "Label");
		~Label() override;

		void Render(core_id idToRender) override;

	private:
		std::string text;
		glm::vec4 color;
	};
}

