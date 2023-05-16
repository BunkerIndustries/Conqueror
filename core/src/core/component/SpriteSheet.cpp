#include "_Core.h"
#include "component/SpriteSheet.h"
#include "renderer/Renderer.h"

namespace core
{
	SpriteSheet::SpriteSheet(glm::vec4 color, Shr<Texture> texture, float spriteWidth, float spriteHeight, float paddingWidth, float paddingHeight, glm::vec2 selectedSprite, bool registerAlphaPixelsToEvent)
		: color(color), texture(texture), spriteWidth(spriteWidth), spriteHeight(spriteHeight),
		paddingWidth(paddingWidth), paddingHeight(paddingHeight), registerAlphaPixelsToEvent(registerAlphaPixelsToEvent)
	{
		Init(texture, selectedSprite);
	}

	void SpriteSheet::Init(Shr<Texture> texture, glm::vec2 selectedSprite)
	{
		this->textureWidth = texture->GetWidth();
		this->textureHeight = texture->GetHeight();
		this->spriteColumns = textureWidth / this->spriteWidth;
		this->spriteRows = textureHeight / this->spriteHeight;

		// sprites are inverted, because of the opengl and stbi axis conflict
		this->selectedSprite.x = spriteColumns - selectedSprite.x;
		this->selectedSprite.y = spriteRows - selectedSprite.y;

		for (int row = 0; row <= spriteRows; row++)
		{
			std::vector<Shr<Sprite>> rowvec;
			for (int column = 0; column <= spriteColumns; column++)
			{
				rowvec.push_back(MakeShr<Sprite>(color, texture, spriteWidth, spriteHeight, paddingWidth, paddingHeight, glm::vec2(column, row), false));
			}
			Sprites.push_back(rowvec);
		}
		ChangeCoords();
	}

	void SpriteSheet::ChangeSprite(glm::vec2 pos)
	{
		this->selectedSprite.x = pos.x;
		this->selectedSprite.y = pos.y;
		ChangeCoords();
	}

	void SpriteSheet::ChangeCoords()
	{
		this->texCoords = Sprites[selectedSprite.y].at(selectedSprite.x)->GetTexCoords();
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