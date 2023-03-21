#pragma once
#include "_Core.h"
#include "utility.h"

#include "core/renderer/Buffer.h"

namespace core
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() override;
		void Unbind() override;

		void AddData(const void* data, uint32_t size) override;

		const BufferLayout& GetLayout() override;

		OpenGLVertexBuffer(BufferLayout& layout, uint32_t size);
		~OpenGLVertexBuffer() override;
	private:
		uint32_t vboID;
		BufferLayout layout;
	};

	class OpenGLElementBuffer : public ElementBuffer
    {
    public:
		void Bind() override;
		void Unbind() override;
		
	    unsigned int GetElementCount() override;
		 
		OpenGLElementBuffer(uint32_t* data, uint32_t count);
	    ~OpenGLElementBuffer() override;
    private:
		uint32_t eboID;
    	uint32_t count;
    };
}