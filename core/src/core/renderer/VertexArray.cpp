#include "_Core.h"
#include "VertexArray.h"

#include "OpenGL/OpenGLVertexArray.h"

#include "renderer/RenderAPI.h"

namespace core {

	Shr<VertexArray> VertexArray::CreateArray()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::NONE: CORE_ASSERT(false, "'NONE' is a non valid API"); return nullptr;
		case RenderAPI::OPENGL: return MakeShr<OpenGLVertexArray>();
		case RenderAPI::VULKAN: CORE_ASSERT(false, "'VULKAN' is currently a not supportet API"); return nullptr;;
		}

		CORE_ASSERT(false, "");
		return nullptr;
	}
}


