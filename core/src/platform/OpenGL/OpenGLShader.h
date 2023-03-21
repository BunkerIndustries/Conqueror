#pragma once
#include "_Core.h"
#include "utility.h"

#include "core/renderer/Shader.h"

namespace core
{
	class OpenGLShader : public Shader
	{
    private:
        int shaderProgrammID = 0;
        bool beingUsed = false;

        std::string vertexSources;
        std::string fragmentSources;
        std::string filePath;

    public:
        explicit OpenGLShader(std::string filePath);
        ~OpenGLShader() override;

        void Compile() override;
        void Bind() override;
        void Unbind() override;

        // upload functions
        void UploadMat4f(const char* varName, glm::mat4 mat4) override;
        void UploadMat3f(const char* varName, glm::mat3 mat3) override;
        void UploadVec4f(const char* varName, glm::vec4 vec4) override;
        void UploadVec3f(const char* varName, glm::vec3 vec3) override;
        void UploadVec2f(const char* varName, glm::vec2 vec2) override;
        void UploadFloat(const char* varName, float value) override;
        void UploadInt(const char* varName, int value) override;
        void UploadIntArray(const char* varName, int arrayLength, int array[]) override;
        void UploadTexture(const char* varName, int slot) override;

	};
	
}

