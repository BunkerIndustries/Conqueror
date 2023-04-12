#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/Shader.h"
#include "renderer/Texture.h"

namespace core {

    using Map = std::unordered_map<std::string, std::shared_ptr<void>>;

    class DataPool {
    private:
        static Map dataPool;

    public:
        // get current shader with the specific string (name)
        static std::shared_ptr<Shader> GetShader(std::string shaderName);
        // search for a texture with the specific string (name)
        static std::shared_ptr<Texture> GetTexture(std::string textureName);
    };

    enum class ProjectionMode { PERSPECTIVE, ORTHOGRAPHIC, SCREEN };
    int ProjectionModeToInt(const ProjectionMode& mode);
}