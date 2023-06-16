#include "_Core.h"
#include "FontRenderer.h"

#include "renderer/Renderer.h"

namespace core
{

	FontRenderer::FontRenderer(glm::vec4 color, std::string text, std::string fontPath, bool registerAlphaPixelsToEvent)
		: color(color), text(text), fontPath(fontPath), registerAlphaPixelsToEvent(registerAlphaPixelsToEvent) { }

	void FontRenderer::ChangeText(std::string text)
	{
		this->text = text;
	}

	void FontRenderer::OnUpdate()
	{
		TextRenderData data;
		data.transform = gameObject->transform;
		data.color = color;
		data.string = text;
		data.font = DataPool::GetFont(fontPath);
		data.mode = gameObject->GetProjectionMode();
		data.coreID = gameObject->GetCoreID();
		data.coreIDToAlphaPixels = registerAlphaPixelsToEvent;
		Renderer::DrawString(data);
	}
};