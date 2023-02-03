#include "_Core.h"

#include "utils/DataPool.h"
#include "renderer/Texture.h"
#include "generic/Shader.h"

namespace core {

    // freetype developers are crazy
    //#include "../lib/freetype/ft2build.h"
    //#include FT_FREETYPE_H

    // declare static maps in order to find a reference
    Map DataPool::data_pool;

    std::shared_ptr<Shader> DataPool::getShader(std::string shaderName) {
        // set default path
        std::string path = "assets/shaders/" + shaderName + ".glsl";
        std::string shader_id = "shader_" + shaderName;

        Map::iterator it = data_pool.find(shader_id);

        std::shared_ptr<Shader> shader;

        if (it == data_pool.end())
        {
            shader = std::make_shared<Shader>(path);
            data_pool.emplace(shader_id, shader);
        }
        else
        {
            shader = std::static_pointer_cast<Shader>(it->second);
        }

        return shader;
    }

    std::shared_ptr<Texture> DataPool::getTexture(std::string textureName) {
        // set default path
        std::string path = "assets/textures/" + textureName;

        std::string texture_id = "texture_" + textureName;

        Map::iterator it = data_pool.find(texture_id);

        std::shared_ptr<Texture> texture;

        if (it == data_pool.end())
        {
            texture = std::make_shared<Texture>(path, textureName);
            data_pool.emplace(texture_id, texture);
        }
        else
        {
            texture = std::static_pointer_cast<Texture>(it->second);
        }

        return texture;
    }

    // basically save our characters we need for rendering into the CharacterPool map
    // each character and it's mandatory values for rendering (advance,... (struct variables)) are
    // saved into a map, which can then be used later on
    // create the texture once, use it anytime else
    // this function should be called at an early stage
    // also, call this function before you would want to use the CharacterPool map...
    /*void DataPool::prepareCharacters()
    {
        // firstly, we need to create freetype's objects in order to use their functions
        FT_Library ftl;

        // typical initializing

        // functions return non-zero on error
        if(FT_Init_FreeType(&ftl))
        {
            Logger::Log("Could not load FreeType Library", Logger::Error);
            return;
        }

        FT_Face face;

        if(FT_New_Face(ftl, "assets/fonts/mononoki.ttf", 0, &face))
        {
            Logger::Log("Could not load font face", Logger::Error);
            return;
        }

        // setting the width to 0, makes the library dynamically adjust based to it's height
        FT_Set_Pixel_Sizes(face, 0, 48);

        // needed in order to store the color of a glyph in one byte
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // iterating through the ascii table
        for(uint8_t i = 0; i < 256; i++)
        {
            // load the character
            if(FT_Load_Char(face, i, FT_LOAD_RENDER))
            {
                Logger::Log("Could not load character", Logger::Error);
            }

            unsigned int textureID;

            // generate texture (space) and save the location of the texture into textureID
            glGenTextures(1, &textureID);

            // bind the texture and specify it's dimension
            // this is needed for specifying the character's sizes
            glBindTexture(GL_TEXTURE_2D, textureID);

            // fill the texture with values of the character
            // the character texture has only one color, as we can limit the color usage to 1 byte
            // one could use any color, but one
            glTexImage2D(GL_TEXTURE_2D, 0, GL_BLUE,
                        face->glyph->bitmap.width, face->glyph->bitmap.rows,
                        0, GL_BLUE, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            // texture settings
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // don't repeat left
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // don't repeat right
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // useful for resizing bigger
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // useful for resizing smaller

            // save the pre-rendered character texture values into the struct
            // then save it into the map, ordered by char
            CharacterTemplateS CharacterTemplate =
            {
                textureID,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            // saving into map
            CharacterPool.insert(std::pair<char, CharacterTemplateS>(i, CharacterTemplate));

            //TODO: fix undefined references
            // argh
        }*/

}
