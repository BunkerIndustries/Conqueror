#include "_Core.h"
#include "Panel.h"

#include "renderer/Renderer.h"

namespace core
{
	Panel::Panel(glm::vec4 color, const Transform& transform, Type type, std::string name)
		: UIObject(name, transform), color(color), type(type) { }

	Panel::~Panel()
	{
	}

	void Panel::Render(core_id idToRender)
	{
		switch (type)
		{
			case Type::Rectangle:
				Renderer::DrawRectangle(globalPos, transform.scale, transform.rotation, color, mode, idToRender);
				break;
			case Type::Triangle:
				Renderer::DrawTriangle(globalPos, transform.scale, transform.rotation, color, mode, idToRender);
				break;
		}
	}
}
