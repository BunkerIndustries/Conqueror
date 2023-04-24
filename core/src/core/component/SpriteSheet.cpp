#include "_Core.h"
#include "component/SpriteSheet.h"
#include "renderer/Renderer.h"

namespace core
{	
	SpriteSheet::SpriteSheet(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, glm::vec2 selectedSprite, bool registerAlphaPixelsToEvent)
		: color(color), texture(texture), spriteWidth(spriteWidth), spriteHeight(spriteHeight), selectedSprite(selectedSprite), registerAlphaPixelsToEvent(registerAlphaPixelsToEvent)
	{
		Init(texture, selectedSprite);
	}

	SpriteSheet::SpriteSheet(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite, bool registerAlphaPixelsToEvent)
		: color(color), texture(texture), spriteWidth(spriteWidth), spriteHeight(spriteHeight), 
		paddingWidth(paddingWidth), paddingHeight(paddingHeight), registerAlphaPixelsToEvent(registerAlphaPixelsToEvent)
	{
		Init(texture, selectedSprite);
	}

	void SpriteSheet::Init(Shr<Texture> texture, glm::vec2 selectedSprite)
	{
		//this->spriteWidth = spriteWidth - paddingWidth;
		//this->spriteHeight = spriteHeight - paddingHeight;
		this->textureWidth = texture->GetWidth();
		this->textureHeight = texture->GetHeight();
		this->spriteColumns = textureWidth / this->spriteWidth;
		this->spriteRows = textureHeight / this->spriteHeight;

		// sprites are inverted, because of the opengl and stbi axis conflict
		this->selectedSprite.x = spriteColumns - selectedSprite.x;
		this->selectedSprite.y = spriteRows - selectedSprite.y;

		ChangeCoords();
	}

	void SpriteSheet::ChangeSprite(glm::vec2 pos)
	{
		this->selectedSprite.x = spriteColumns - pos.x;
		this->selectedSprite.y = spriteRows - pos.y;
		ChangeCoords();
	}

	void SpriteSheet::ChangeCoords()
	{
		this->texCoords[0] = { (spriteWidth * selectedSprite.x - paddingWidth)       / textureWidth, (spriteHeight * selectedSprite.y)       / textureHeight };
		this->texCoords[1] = { (spriteWidth * (selectedSprite.x + 1) - paddingWidth) / textureWidth, (spriteHeight * selectedSprite.y)       / textureHeight };
		this->texCoords[2] = { (spriteWidth * (selectedSprite.x + 1) - paddingWidth) / textureWidth, (spriteHeight * (selectedSprite.y + 1)) / textureHeight };
		this->texCoords[3] = { (spriteWidth * selectedSprite.x - paddingWidth)       / textureWidth, (spriteHeight * (selectedSprite.y + 1)) / textureHeight };
	
		// this fixes the unknown offset
		for (int i = 0; i < 4; i++)
		{
			//this->texCoords[i].x -= (spriteWidth / textureWidth) / 2;
			this->texCoords[i].y -= (spriteHeight / textureHeight) / 2;
		}

	}
	void SpriteSheet::OnUpdate()
	{
		EdgeRenderData data;
		data.transform = gameObject->transform;
		data.color = color;
		data.texture = texture;
		std::copy(std::begin(texCoords), std::end(texCoords), std::begin(data.texCoords));
		data.mode = gameObject->GetProjectionMode();
		data.coreID = gameObject->GetCoreID();
		data.coreIDToAlphaPixels = registerAlphaPixelsToEvent;
		Renderer::DrawRectangle(data);
	}

	void SpriteSheet::OnImgui(float dt)
	{

	}

};