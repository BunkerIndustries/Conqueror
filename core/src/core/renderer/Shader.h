#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Compile() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        // upload functions
        virtual void UploadMat4f(const char* varName, glm::mat4 mat4) = 0;
        virtual void UploadMat3f(const char* varName, glm::mat3 mat3) = 0;
        virtual void UploadVec4f(const char* varName, glm::vec4 vec4) = 0;
        virtual void UploadVec3f(const char* varName, glm::vec3 vec3) = 0;
        virtual void UploadVec2f(const char* varName, glm::vec2 vec2) = 0;
        virtual void UploadFloat(const char* varName, float value) = 0;
        virtual void UploadInt(const char* varName, int value) = 0;
        virtual void UploadIntArray(const char* varName, int arrayLength, int array[]) = 0;
        virtual void UploadTexture(const char* varName, int slot) = 0;

        static Shr<Shader> CreateShader(std::string filePath);
    };
}
