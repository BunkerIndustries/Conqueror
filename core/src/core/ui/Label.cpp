#include "_Core.h"
#include "Label.h"

#include "renderer/Renderer.h"


namespace core
{
	Label::Label(std::string text, glm::vec4 color, const Transform& transform, std::string name)
		: UIObject(name, transform), text(text), color(color)
	{
	}

	Label::~Label()
	{
	}

	void Label::Render(core_id idToRender)
	{
		Renderer::DrawString(globalPos, transform.scale, transform.rotation, color, text, Font::GetFont("assets/fonts/mononoki.ttf"), mode, idToRender);
	}

}
