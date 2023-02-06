#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/VertexArray.h";
#include "renderer/RendererAPI.h"

namespace core {
	class RenderCommand
	{
	private:
		static Shr<RendererAPI> rendererAPI;

	public:
		inline static void Init()
		{
			rendererAPI->Init();
		}

		inline static void Clear(glm::vec4 color)
		{
			rendererAPI->Clear(color);
		}

		inline static void DrawElements(Shr<VertexArray>& vertexArray)
		{
			rendererAPI->DrawElements(vertexArray);
		}

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			rendererAPI->SetViewPort(x, y, width, height);
		}
	};

}

