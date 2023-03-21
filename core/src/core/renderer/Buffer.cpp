#include "_Core.h"
#include "Buffer.h"

#include "RenderAPI.h"

#include "OpenGL/OpenGLBuffer.h"

namespace core
{
	Shr<VertexBuffer> VertexBuffer::CreateBuffer(BufferLayout& layout, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::NONE: CORE_ASSERT(false, "'NONE' is a non valid API"); return nullptr;
		case RenderAPI::OPENGL: return MakeShr<OpenGLVertexBuffer>(layout, size);
		case RenderAPI::VULKAN: CORE_ASSERT(false, "'VULKAN' is currently a not supportet API"); return nullptr;;
		}

		CORE_ASSERT(false, "");
		return nullptr;
	}

	Shr<ElementBuffer> ElementBuffer::CreateBuffer(uint32_t* data, uint32_t count)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::NONE: CORE_ASSERT(false, "'NONE' is a non valid API"); return nullptr;
		case RenderAPI::OPENGL: return MakeShr<OpenGLElementBuffer>(data, count);
		case RenderAPI::VULKAN: CORE_ASSERT(false, "'VULKAN' is currently a not supportet API"); return nullptr;;
		}

		CORE_ASSERT(false, "");
		return nullptr;
	}
	
}
