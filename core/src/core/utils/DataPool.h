#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Shader.h"
#include "renderer/Texture.h"

namespace core {

    /*struct CharacterTemplateS
    {
        unsigned int textureID; // texture ID, used by opengl
        glm::ivec2 size; // size of character
        glm::ivec2 bearing; // height offset
        unsigned int advance; // width offset
    };*/
    using Map = std::unordered_map<std::string, std::shared_ptr<void>>;

    class CORE_API DataPool {
    private:
        static Map data_pool;

    public:
        // get current shader with the specific string (name)
        static std::shared_ptr<Shader> getShader(std::string shaderName);
        // search for a texture with the specific string (name)
        static std::shared_ptr<Texture> getTexture(std::string textureName);
        

        //static void prepareCharacters();
        
    };

    enum class ProjectionMode { SCREEN, PERSPECTIVE, ORTHOGRAPHIC };

}