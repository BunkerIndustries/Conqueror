#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Sound.h"

namespace core {

    using Map = std::unordered_map<std::string, std::shared_ptr<void>>;

    class Shader;
    class Texture;
    class Font;

    class DataPool {
    private:
        static Map dataPool;

    public:
        // get current shader with the specific string (name)
        static Shr<Shader> GetShader(std::string shaderName);
        // search for a texture with the specific string (name)
        static Shr<Texture> GetTexture(std::string textureName);

        static Shr<Font> GetFont(std::string fontName);

        static Sound SoundSystem;

        static void InitSoundSystem();
    };

    enum class ProjectionMode { PERSPECTIVE, ORTHOGRAPHIC, SCREEN };
    int ProjectionModeToInt(const ProjectionMode& mode);
}