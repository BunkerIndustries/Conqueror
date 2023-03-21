#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/VertexArray.h"

namespace core
{
    class OpenGLVertexArray : public VertexArray
	{
	public:
		void Bind() override;
		void Unbind() override;

		void SetVertexBuffer(Shr<VertexBuffer>& vertexBuffer) override;
		void SetElementBuffer(Shr<ElementBuffer>& elementBuffer) override;

		Shr<VertexBuffer>& GetVertexBuffer()override { return vertexBuffer; }
		Shr<ElementBuffer>& GetElementBuffer() override { return elementBuffer; }

        OpenGLVertexArray();
		~OpenGLVertexArray() override;
	private:
		uint32_t vaoID;
		uint32_t vboIndex = 0;

		Shr<VertexBuffer> vertexBuffer;
		Shr<ElementBuffer> elementBuffer;
	};
}