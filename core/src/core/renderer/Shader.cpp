#include "_Core.h"
#include "renderer/Shader.h"

#include "RenderAPI.h"

#include "OpenGL/OpenGLShader.h"


namespace core {
	Shr<Shader> Shader::CreateShader(std::string filePath)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::NONE: CORE_ASSERT(false, "'NONE' is a non valid API"); return nullptr;
		case RenderAPI::OPENGL: return MakeShr<OpenGLShader>(filePath);
		case RenderAPI::VULKAN: CORE_ASSERT(false, "'VULKAN' is currently a not supportet API"); return nullptr;;
		}

		CORE_ASSERT(false, "");
		return nullptr;
	}
}
