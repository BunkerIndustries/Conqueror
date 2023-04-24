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
		EdgeRenderData data;
		data.transform = { globalPos, transform.scale, transform.rotation };
		data.color = color;
		data.mode = mode;
		data.coreID = idToRender;

		switch (type)
		{
			case Type::Rectangle:
				Renderer::DrawRectangle(data);
				break;
			case Type::Triangle:
				Renderer::DrawTriangle(data);
				break;
		}
	}
}
