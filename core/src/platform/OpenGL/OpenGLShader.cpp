#include "_Core.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace core
{
    OpenGLShader::OpenGLShader(std::string filePath) {
        this->filePath = filePath;
        std::ifstream ifs(filePath);
        if (!ifs) {
            LOG_CORE_ERROR("Could not load shader: '" + std::string(filePath) + "'");
            return;
        }

        // this magic saves the file into the string
        std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

        // declare shader structure
        int vertexPos = content.find("#type vertex");
        int fragmentPos = content.find("#type fragment");

        for (int i = vertexPos + 13; i < fragmentPos; i++) {
            vertexSources += content[i];
        }
        for (int i = fragmentPos + 15; i < (int)content.size(); i++) {
            fragmentSources += content[i];
        }
        LOG_CORE_TRACE("Loaded shader: '" + filePath + "'");
    }
    OpenGLShader::~OpenGLShader() { }

    void OpenGLShader::Compile() {
        //Compile and link shaders
        int vertexID, fragmentID;

        //error vars:
        int isCompiled = 0, len = 0;

        //vertex shader
        vertexID = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* vsource = (const GLchar*)vertexSources.c_str();
        glad_glShaderSource(vertexID, 1, &vsource, 0); //Retrieves the vertex shader source code

        glCompileShader(vertexID);

        //error handling
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &len);
            char vertexError[1000] = {};
            glGetShaderInfoLog(vertexID, len, NULL, &vertexError[0]);

            LOG_CORE_ERROR("'" + filePath + "'\n\tVertex shader compilation failed.\n" + &vertexError[0]);
        }

        //fragment shader
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar* fsource = (const GLchar*)fragmentSources.c_str();
        glad_glShaderSource(fragmentID, 1, &fsource, 0); //Retrieves the fragment shader source code

        glCompileShader(fragmentID);

        // error handling, if it did not compile correctly report random stuff
        glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &len);
            std::vector<char> v(len);
            char fragmentError[1000] = {};
            glGetShaderInfoLog(fragmentID, len, NULL, &fragmentError[0]);

            LOG_CORE_ERROR("'" + filePath + "'\n\tFragment shader compilation failed.\n" + &fragmentError[0]);
        }

        //linking
        shaderProgrammID = glCreateProgram();
        glAttachShader(shaderProgrammID, vertexID);
        glAttachShader(shaderProgrammID, fragmentID);
        glLinkProgram(shaderProgrammID);

        //error handling
        //glGetShaderiv(shaderProgrammID, GL_LINK_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE) {
            glGetShaderiv(shaderProgrammID, GL_INFO_LOG_LENGTH, &len);
            char linkingError[1000] = {};
            glGetShaderInfoLog(shaderProgrammID, len, NULL, &linkingError[0]);
        
            LOG_CORE_ERROR("'" + filePath + "'\n\tLinking of shaders failed!\n" + &linkingError[0]);
        }

        LOG_CORE_TRACE("Compiled shader '" + filePath + "' ");
    }

    void OpenGLShader::Bind() {
        glUseProgram(shaderProgrammID);
    }

    void OpenGLShader::Unbind() {
        glUseProgram(0);
    }

    // upload different types to the shader

    void OpenGLShader::UploadMat4f(const char* varName, glm::mat4 mat4) {
        // save uniform to variable and tell the shader where it is, with the variable
        // use == is required in order to upload it to the current shader with ,,shaderProgrammID'' (grammar police is haunting you pascal)
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat4));
    }

    void OpenGLShader::UploadMat3f(const char* varName, glm::mat3 mat3) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniformMatrix3fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat3));
    }

    void OpenGLShader::UploadVec4f(const char* varName, glm::vec4 vec4) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform4f(varLocation, vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void OpenGLShader::UploadVec3f(const char* varName, glm::vec3 vec3) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform3f(varLocation, vec3.x, vec3.y, vec3.z);
    }

    void OpenGLShader::UploadVec2f(const char* varName, glm::vec2 vec2) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform2f(varLocation, vec2.x, vec2.y);
    }

    void OpenGLShader::UploadFloat(const char* varName, float value) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform1f(varLocation, value);
    }

    void OpenGLShader::UploadInt(const char* varName, int value) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform1i(varLocation, value);
    }

    void OpenGLShader::UploadIntArray(const char* varName, int arrayLength, int array[]) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform1iv(varLocation, arrayLength, array);
    }

    void OpenGLShader::UploadTexture(const char* varName, int slot) {
        int varLocation = glGetUniformLocation(shaderProgrammID, varName);
        Bind();
        glUniform1i(varLocation, slot);
    }
}