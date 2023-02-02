#pragma once
#include "_Core.h"

namespace core {

    class Shader {
    private:
        int shaderProgrammID = 0;
        bool beingUsed = false;

        std::string vertexSources;
        std::string fragmentSources;
        std::string filePath;

    public:
        explicit Shader(std::string filePath);
        ~Shader();
        void compile();
        void use();
        void detach();

        // upload functions
        void uploadMat4f(const char* varName, glm::mat4 mat4);
        void uploadMat3f(const char* varName, glm::mat3 mat3);
        void uploadVec4f(const char* varName, glm::vec4 vec4);
        void uploadVec3f(const char* varName, glm::vec3 vec3);
        void uploadVec2f(const char* varName, glm::vec2 vec2);
        void uploadFloat(const char* varName, float value);
        void uploadInt(const char* varName, int value);
        void uploadIntArray(const char* varName, int arrayLength, int array[]);
        void uploadTexture(const char* varName, int slot);
    };

}