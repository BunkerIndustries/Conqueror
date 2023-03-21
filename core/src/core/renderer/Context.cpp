#include "_Core.h"
#include "Context.h"

#include "RenderAPI.h"

#include "OpenGL/OpenGLContext.h"

namespace core {
	Shr<Context> Context::CreateContext(void* window)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::NONE: CORE_ASSERT(false, "'NONE' is a non valid API"); return nullptr;
		case RenderAPI::OPENGL: return MakeShr<OpenGLContext>(window);
		case RenderAPI::VULKAN: CORE_ASSERT(false, "'VULKAN' is currently a not supportet API"); return nullptr;;
		}

		CORE_ASSERT(false, "");
		return nullptr;
	}
}
