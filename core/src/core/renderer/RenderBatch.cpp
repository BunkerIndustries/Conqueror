#include "_Core.h"

#include "renderer/RenderBatch.h"
#include "utils/DataPool.h"
#include "generic/Window.h"
#include "component/SpriteRenderer.h"
#include "generic/GameObject.h"
#include "generic/Application.h"

#include <GLAD/glad.h>

namespace core {

    RenderBatch::RenderBatch(int maxBatchSize, int zIndex, DataPool::DISPLAYMODE displaymode)
    {
        // set local and current values
        this->zIndex = zIndex;
        this->maxBatchSize = maxBatchSize;
        this->elements = new unsigned int[maxBatchSize * 6];
        this->displayMode = displaymode;
        numSprites = 0;

        // menu gui mode needs a special shader because of uProjection is aPos basically
        if (displaymode == DataPool::DISPLAYMODE::NONE)
        {
            shader = DataPool::getShader("menu");
        }
        else
        {
            // orthographic and and perspective camera modes can be utlilized by the default shader
            shader = DataPool::getShader("default");
        }

        shader->compile();
        RenderBatch::hasRoom_bool = true;

        // we do not need this because the SPRITERENDERER does it for us
        //loadVertexProperties(0);
    }

    RenderBatch::~RenderBatch() {
        delete elements;
    };

    void RenderBatch::start() {
        // generate vertex buffer
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // allocate space for vertex array
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        // put everything from the vector into the array, so that we can access it from within gl functions || using vectors makes it easier for dynamic allocations
        // create task for gpu and save data
        glBufferData(GL_ARRAY_BUFFER, maxBatchSize * VERTEX_SIZE_BYTES * 4, vertices.data(), GL_DYNAMIC_DRAW);
        //element buffer object (useful for creating squares)

        glGenBuffers(1, &eboID);
        // create array
        
        // initialize array values
        generateIndices(elements);
        // use the array
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * maxBatchSize * 6, elements, GL_DYNAMIC_DRAW);

        // saving / uploading points (x,y) to vertex slot 0
        //declaration of vertex basically (start at byte offset x, array index y,...)
        // POSITION
        glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)POS_OFFSET);
        glEnableVertexAttribArray(0);

        // saving / uploading color into vertex, slot 1, 4 parameters, and start at the offset of 8 bytes (array index 2)
        // declaration of vertex
        // COLOR
        glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)COLOR_OFFSET);
        glEnableVertexAttribArray(1);

        // 1. slot  2. attribute number 3. type  4. normalization    5. sizeof a vertex (one line) 6. byte offset
        // TEXTURE_COORDINATES
        glVertexAttribPointer(2, TEX_COORDS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEX_COORDS_OFFSET);
        glEnableVertexAttribArray(2);

        //TEXTURE_ID
        glVertexAttribPointer(3, TEX_ID_SIZE, GL_INT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEX_ID_OFFSET);
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);
    }

    void RenderBatch::addSprite(SpriteRenderer* sprite_renderer) {
        // add sprite to renderbatch
        // add it to the last row and increase the amount of sprites we have in the variable
        int index = this->numSprites;
        sprites.insert(sprites.end(), sprite_renderer);
        numSprites++;

        // if the sprite render has a texture, give it to the renderbatch, so that he can use (render) it
        updateTextures();

        // just some checking, if the maxBatchSize is being overridden don't load any more textures (hasRoom_bool)
        // load vertex properties at current index of the spriterenderer (this is why we do not need to do it manually anymore)
        loadVertexProperties(index);

        if (numSprites >= maxBatchSize) {
            this->hasRoom_bool = false;
        }
    }

    bool RenderBatch::hasSprite(SpriteRenderer* sprite_renderer)
    {
        return std::find(sprites.begin(), sprites.end(), sprite_renderer) != sprites.end();
    }


    void RenderBatch::updateTextures() {
        textures.erase(textures.begin(), textures.end());
        for (int i = 0; i < numSprites; i++) {
            if (sprites[i]->getTexture() != nullptr && !hasTexture(sprites[i]->getTexture())) {
                textures.insert(textures.end(), sprites[i]->getTexture());
            }
        }
    }

    void RenderBatch::render() {
        // set spriterenderer to sprites
        // and if there are changes, display them to the renderer
        // after the vertex array has been updated, setClean to say that there are no more changes for now
        // this is needed in order to see the changes
        bool reloadVertexArray = false;
        for (int i = 0; i < numSprites; i++) {
            SpriteRenderer* spriteRenderer = sprites[i];
            if (spriteRenderer->getIsDirty()) {
                updateTextures();
                loadVertexProperties(i);

                spriteRenderer->setClean();
                reloadVertexArray = true;
            }
        }
        // reload the vertex array if there have been made changes
        if (reloadVertexArray) {
            // updates the vertex array in order to see the changes within rendering
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, maxBatchSize * VERTEX_SIZE_BYTES * 4, vertices.data());
        }

        // use the shader and upload the shader variables
        shader->use();

        if (displayMode == DataPool::DISPLAYMODE::ORTHOGRAPHIC)
        {
            shader->uploadMat4f("uProjection", Application::getCurrentScene()->getCamera()->getOrthographicMatrix());
        }
        else if (displayMode == DataPool::DISPLAYMODE::PERSPECTIVE)
        {
            shader->uploadMat4f("uProjection", Application::getCurrentScene()->getCamera()->getProjectionMatrix());
        }
        else if (displayMode == DataPool::DISPLAYMODE::NONE)
        {
            shader->uploadVec2f("uProjection", glm::vec2(vertices[POS_OFFSET], vertices[POS_OFFSET + 1]));
        }
        // fov
        shader->uploadMat4f("uView", Application::getCurrentScene()->getCamera()->getViewMatrix());

        for (int i = 0; i < textures.size(); i++)
        {
            // activate all created textures
            textures[i]->bind(i);
        }
        // upload the texture array into the shader
        // convert vector to array in order to pass the parameters through
        int* texArray = new int[texSlots.size()];
        std::copy(texSlots.begin(), texSlots.end(), texArray);
        shader->uploadIntArray("uTexture", texSlots.size(), texArray);
        delete texArray;

#ifdef BUILD_DEBUG
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
#endif

        glBindVertexArray(vaoID);
        // draw both (with coords and color)
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // 6 = 6 points for 2 triangles
        glDrawElements(GL_TRIANGLES, this->numSprites * 6, GL_UNSIGNED_INT, nullptr);
        draw_calls++;

        // stop drawing and disable array (finish it off)
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // unbind everything

        glBindVertexArray(0);
        for (int i = 0; i < textures.size(); i++)
        {
            textures[i]->unbind();
        }
        shader->detach();
    }

    void RenderBatch::loadVertexProperties(int index) {
        SpriteRenderer* sprite = sprites[index];
        
        // find offset in vertex array
        int offset = index * 4 * VERTEX_SIZE;

        // just set the texture variables from our texCoords definition in class Sprite
        glm::vec4 color = sprite->getColor();
        glm::vec2 texCoord[] = { glm::vec2(sprite->getTexCoords()[0], sprite->getTexCoords()[1]),
                                glm::vec2(sprite->getTexCoords()[2], sprite->getTexCoords()[3]),
                                glm::vec2(sprite->getTexCoords()[4], sprite->getTexCoords()[5]),
                                glm::vec2(sprite->getTexCoords()[6], sprite->getTexCoords()[7])
        };

        //Logger::Log("---------------------------------");
    //
        //for (int i = 0; i < textures.size(); i++) {
        //    Logger::Log(textures[i]->getFilePath());
        //}

        // set the texID appropriately in order to load it into the shader
        // if there is a texture, set the texture ID accordingly to it's value
        int texID = -1;
        if (sprite->getTexture() != nullptr)
        {
            for (int i = 0; i < textures.size(); i++)
            {
                if (textures[i] == sprite->getTexture())
                {
                    texID = i;
                    break;
                }
            }
        }

        //Logger::Log(std::to_string(texID));


        // set vertex array functionally and recursively with the gained information from the user
        // for more information, see the standard declaration of a vertex array with 2 triangles
        // we are not using the third dimension in our case, on could adjust it, but no

        /*
        static float vertexArray[] = {
            //position          //color                     //texture coords  //texture ID
              -0.5f, -0.5f,     1.0f, 0.0f, 0.0f, 0.5f,     0.0f, 0.0f,       0.0f,        //Bottom Left (0)
               0.5f, -0.5f,     1.0f, 1.0f, 0.0f, 0.8f,     1.0f, 0.0f,       0.0f,        //Bottom Right (1)
               0.5f,  0.5f,     1.0f, 0.0f, 1.0f, 0.2f,     1.0f, 1.0f,       0.0f,        //Top Right (2)
              -0.5f,  0.5f,     1.0f, 0.0f, 1.0f, 0.4f,     0.0f, 1.0f,       0.0f         //Top left (3)
        };
        // square geometry / order
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        */

        float xAdd = -0.5f;
        float yAdd = -0.5f;
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 1:
                xAdd = 0.5f;
                break;
            case 2:
                yAdd = 0.5f;
                break;
            case 3:
                xAdd = -0.5f;
                break;
            default:
                break;
            }
            // this is the recursive vertices creation
            // set the first values to the according positions

            if (vertices.size() > offset + 8) {
                vertices[offset + 0] = sprite->GetGameObject()->transform.position.x + xAdd * sprite->GetGameObject()->transform.scale.x;
                vertices[offset + 1] = sprite->GetGameObject()->transform.position.y + yAdd * sprite->GetGameObject()->transform.scale.y;

                // set colors
                vertices[offset + 2] = color.x;
                vertices[offset + 3] = color.y;
                vertices[offset + 4] = color.z;
                vertices[offset + 5] = color.w;

                // set texture coordinates
                vertices[offset + 6] = texCoord[i].x;
                vertices[offset + 7] = texCoord[i].y;

                // set texture id
                vertices[offset + 8] = texID;
            }
            else {
                vertices.emplace(vertices.begin() + offset + 0, sprite->GetGameObject()->transform.position.x + xAdd * sprite->GetGameObject()->transform.scale.x);
                vertices.emplace(vertices.begin() + offset + 1, sprite->GetGameObject()->transform.position.y + yAdd * sprite->GetGameObject()->transform.scale.y);

                // set colors
                vertices.emplace(vertices.begin() + offset + 2, color.x);
                vertices.emplace(vertices.begin() + offset + 3, color.y);
                vertices.emplace(vertices.begin() + offset + 4, color.z);
                vertices.emplace(vertices.begin() + offset + 5, color.w);

                // set texture coordinates
                vertices.emplace(vertices.begin() + offset + 6, texCoord[i].x);
                vertices.emplace(vertices.begin() + offset + 7, texCoord[i].y);

                // set texture id
                vertices.emplace(vertices.begin() + offset + 8, texID);
            }
            // set offset to the next line for a next triangle in order to make use of batch rendering
            offset += VERTEX_SIZE;
        }
    }

    void RenderBatch::generateIndices(unsigned int* element) {
        // 2 triangles to display one square
        for (int i = 0; i < maxBatchSize; i++)
        {
            loadElementIndices(element, i);
        }
    }

    void RenderBatch::loadElementIndices(unsigned int* arrayElements, int index) {
        int offsetArrayIndex = 6 * index;
        int offset = 4 * index;

        // first triangle
        arrayElements[offsetArrayIndex + 0] = offset + 3;
        arrayElements[offsetArrayIndex + 1] = offset + 2;
        arrayElements[offsetArrayIndex + 2] = offset + 0;

        // second triangle
        arrayElements[offsetArrayIndex + 3] = offset + 0;
        arrayElements[offsetArrayIndex + 4] = offset + 2;
        arrayElements[offsetArrayIndex + 5] = offset + 1;
    }

    bool RenderBatch::hasRoom() {
        return hasRoom_bool;
    }

    bool RenderBatch::hasTextureRoom() {
        return textures.size() < 8;
    }

    bool RenderBatch::hasTexture(std::shared_ptr<Texture> tex) {
        // check if the desired texture is being used in the current renderbatch
        for (auto& texture : textures) {
            if (tex == texture) {
                return true;
            }
        }
        return false;
    }

    int RenderBatch::getZIndex() {
        // do you really need an explanation for this
        return this->zIndex;
    }

    int RenderBatch::GetSpritesCount() const
    {
        return numSprites;
    }

    int RenderBatch::GetVertexCount() const
    {
        return vertices.size() / VERTEX_SIZE;
    }
}
