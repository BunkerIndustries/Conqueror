#include "_Core.h"
#include "Button.h"

#include "renderer/Renderer.h"


namespace core
{
	Button::Button(glm::vec4 color, const Transform& transform, Type type, const ButtonEventCallbackFunction& buttonEventFunction, std::string name)
		: UIObject(name, transform), color(color), type(type), buttonEventFunction(buttonEventFunction)
	{
		buttonID = coreID;
	}

	Button::~Button()
	{
	}

	void Button::Render(core_id idToRender)
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
