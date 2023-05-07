#pragma once
#include "_Core.h"
#include "utility.h"

#include "UIObject.h"

namespace core
{
	class PictureBox : public UIObject
	{
	public:
		PictureBox(glm::vec4 color, const Transform& transform, Shr<Texture> texture, Type type, std::string name = "PictureBox");
		PictureBox(glm::vec4 color, const Transform& transform, Shr<Texture> texture, float tilingFactor, Type type, std::string name = "Panel");
		~PictureBox() override;
		void Render(core_id idToRender) override;

	private:
		Shr<Texture> texture;
		float tilingFactor;
		Type type;
	};
	
}
