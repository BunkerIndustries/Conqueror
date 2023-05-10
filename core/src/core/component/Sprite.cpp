#include "_Core.h"
#include "Sprite.h"

namespace core
{
	Sprite::Sprite(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite, bool registerAlphaPixelsToEvent)
	{
		this->textureWidth = texture->GetWidth();
		this->textureHeight = texture->GetHeight();
		this->color = color;
		this->texture = texture;
		spriteWidth *= 2;
		//spriteHeight *= 2;
		paddingWidth *= 2;
		paddingHeight *= 8;

		// create texcoords
		texcoords[0] = { (spriteWidth * selectedSprite.x + paddingWidth) / textureWidth, (spriteHeight * selectedSprite.y - paddingHeight) / textureHeight };
		texcoords[1] = { (spriteWidth * (selectedSprite.x + 1) + paddingWidth) / textureWidth, (spriteHeight * selectedSprite.y - paddingHeight) / textureHeight };
		texcoords[2] = { (spriteWidth * (selectedSprite.x + 1) + paddingWidth) / textureWidth, (spriteHeight * (selectedSprite.y + 1) - paddingHeight) / textureHeight };
		texcoords[3] = { (spriteWidth * selectedSprite.x + paddingWidth) / textureWidth, (spriteHeight * (selectedSprite.y + 1) - paddingHeight) / textureHeight };

		// this fixes the unknown offset
		for (int i = 0; i < 4; i++)
		{
			//this->texCoords[i].x -= (spriteWidth / textureWidth) / 2;
			texcoords[i].y -= (spriteHeight / textureHeight) / 2;
		}
	}

	Sprite::~Sprite()
	{

	}

	glm::vec4 Sprite::GetColor() const
	{
		return color;
	}

	Shr<Texture> Sprite::GetTexture() const
	{
		return texture;
	}
	
	std::array<glm::vec2, 4> Sprite::GetTexCoords() const
	{
		return texcoords;
	}

};