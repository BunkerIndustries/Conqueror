#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/Buffer.h"


namespace core
{
	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetVertexBuffer(Shr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetElementBuffer(Shr<ElementBuffer>& elementBuffer) = 0;

		virtual Shr<VertexBuffer>& GetVertexBuffer() = 0;
		virtual Shr<ElementBuffer>& GetElementBuffer() = 0;

		virtual ~VertexArray() = default;

		static Shr<VertexArray> CreateArray();
	};
}

