#pragma once
#include "_Core.h"

#include "UIObject.h"

namespace core
{
	class Panel : public UIObject
	{
	public:
		Panel(glm::vec4 color, const Transform& transform, Type type, std::string name = "Panel");
		~Panel() override;

		void Render(core_id idToRender) override;

	private:
		Type type;
	};
}

