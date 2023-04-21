#include "_Core.h"
#include "Label.h"

#include "renderer/Renderer.h"


namespace core
{
	Label::Label(std::string text, glm::vec4 color, const Transform& transform, const Shr<Font>& font, std::string name)
		: UIObject(name, transform), text(text), color(color), font(font)
	{
	}

	Label::~Label()
	{
	}

	void Label::Render(core_id idToRender)
	{
		Renderer::DrawString(globalPos, transform.scale, transform.rotation, color, text, font, mode, idToRender);
	}

}
