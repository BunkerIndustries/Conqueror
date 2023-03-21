#include "_Core.h"
#include "Framebuffer.h"

#include "RenderAPI.h"

#include "OpenGL/OpenGLFramebuffer.h"

namespace core {

	Shr<Framebuffer> Framebuffer::CreateBuffer(const FramebufferSpecification& specification)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::NONE: CORE_ASSERT(false, "'NONE' is a non valid API"); return nullptr;
		case RenderAPI::OPENGL: return MakeShr<OpenGLFramebuffer>(specification);
		case RenderAPI::VULKAN: CORE_ASSERT(false, "'VULKAN' is currently a not supportet API"); return nullptr;;
		}

		CORE_ASSERT(false, "");
		return nullptr;
	}
}