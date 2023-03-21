#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/VertexArray.h"
#include "renderer/RenderAPI.h"

namespace core {
	class RenderCommand
	{
	private:
		static Shr<RenderAPI> rendererAPI;

	public:
		inline static void Init()
		{
			rendererAPI->Init();
		}

		inline static void ClearColor(glm::vec4& color)
		{
			rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			rendererAPI->Clear();
		}

		inline static void DrawElements(Shr<VertexArray>& vertexArray, uint32_t elementCount)
		{
			rendererAPI->DrawElements(vertexArray, elementCount);
		}

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			rendererAPI->SetViewPort(x, y, width, height);
		}
	};

}

