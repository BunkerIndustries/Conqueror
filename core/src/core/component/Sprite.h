#pragma once
#include "_Core.h"

#include "renderer/Texture.h"

namespace core
{
	class Sprite
	{
	public:
		Sprite(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite, bool registerAlphaPixelsToEvent = false);
		~Sprite();

		glm::vec4 GetColor() const;
		Shr<Texture> GetTexture() const;
		std::array<glm::vec2, 4> GetTexCoords() const;

	private:
		float textureWidth;
		float textureHeight;
		
		glm::vec4 color;

		Shr<Texture> texture;
		
		std::array<glm::vec2, 4> texcoords;
	};
}

