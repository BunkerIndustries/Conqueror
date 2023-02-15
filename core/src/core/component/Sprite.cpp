#include "_Core.h"

#include "component/Sprite.h"
#include "renderer/Texture.h"

namespace core {

    Sprite::Sprite(std::shared_ptr<Texture> texture)
	{
        this->texture = texture;
        // standard texture coordinates (mostly used)
        int offset = 0;
        float xAdd = 0.0f;
        float yAdd = 0.0f;

        // this is just a magic looking way in order to not look like idiots (kinda prevented harcode)
        for (int i = 0; i < 4; i++) {
            switch (i) {
            case 1:
                xAdd = 1.0f;
                break;
            case 2:
                yAdd = 1.0f;
                break;
            case 3:
                xAdd = 0.0f;
                break;
            }
            // refresh the texture coordinate values
            texCoords[offset] = xAdd;
            texCoords[offset + 1] = yAdd;
            // increment with 2 because there are 2 new points (x and y)
            offset += 2;
        }
    }


    Sprite::Sprite(std::shared_ptr<Texture> texture, float texCoords[])
	{
    // set current texture to desired texture
        Sprite::texture = texture;
        // get texCoords array and set the desired values (this is rarely being called) who the hell would want a flipped texture
        for (int i = 0; i < 8; i++) {
            this->texCoords[i] = texCoords[i];
        }
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::setTexture(std::shared_ptr<Texture> texture) {
        this->texture = texture;
    }

    std::shared_ptr<Texture> Sprite::getTexture()
    {
        // get current texture
        return this->texture;
    }

    float* Sprite::getTexCoords()
    {
        // get current texture coordinates
        return this->texCoords;
    }

}