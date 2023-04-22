#include "_Core.h"
#include "FontRenderer.h"

#include "renderer/Renderer.h"

namespace core
{

	FontRenderer::FontRenderer(glm::vec4 color, std::string text, std::string fontPath)
		: color(color), text(text), fontPath(fontPath) { }

	void FontRenderer::ChangeText(std::string text)
	{
		this->text = text;
	}

	void FontRenderer::OnUpdate()
	{
		Renderer::DrawString(gameObject->transform.position, gameObject->transform.scale, gameObject->transform.rotation, color, text, DataPool::GetFont(fontPath), gameObject->GetProjectionMode(), gameObject->GetCoreID());
	}
};