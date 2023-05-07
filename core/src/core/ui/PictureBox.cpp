#include "_Core.h"
#include "PictureBox.h"

#include "renderer/Renderer.h"


namespace core
{
	PictureBox::PictureBox(glm::vec4 color, const Transform& transform, Shr<Texture> texture, Type type,
		std::string name)
			: UIObject(name, transform, color), texture(texture), tilingFactor(1.0f), type(type)
	{
	}

	PictureBox::PictureBox(glm::vec4 color, const Transform& transform, Shr<Texture> texture, float tilingFactor,
		Type type, std::string name)
			: UIObject(name, transform, color), texture(texture), tilingFactor(tilingFactor), type(type)
	{
	}

	PictureBox::~PictureBox()
	{
	}

	void PictureBox::Render(core_id idToRender)
	{
		EdgeRenderData data;
		data.transform = { globalPos, globalScale, transform.rotation };
		data.color = color;
		data.mode = mode;
		data.coreID = idToRender;
		data.texture = texture;
		data.tilingFactor = tilingFactor;

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
