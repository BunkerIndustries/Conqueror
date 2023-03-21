#include "_Core.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace core
{
	//
	// VERTEX BUFFER
	//

	OpenGLVertexBuffer::OpenGLVertexBuffer(BufferLayout& layout, uint32_t size)
		: layout(layout)
	{
		glCreateBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &vboID);
	}

	void OpenGLVertexBuffer::AddData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout()
	{
		return this->layout;
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//
	// ELEMENT BUFFER
	//

	OpenGLElementBuffer::OpenGLElementBuffer(uint32_t* data, uint32_t count)
		:count(count)
	{
		glCreateBuffers(1, &eboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
	}

	OpenGLElementBuffer::~OpenGLElementBuffer()
	{
		glDeleteBuffers(1, &eboID);
	}

	unsigned OpenGLElementBuffer::GetElementCount()
	{
		return count;
	}

	void OpenGLElementBuffer::Bind() 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	}

	void OpenGLElementBuffer::Unbind() 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}