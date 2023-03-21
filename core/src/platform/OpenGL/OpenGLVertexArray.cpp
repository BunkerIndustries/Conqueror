#include "_Core.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace core
{
	static GLenum GLSLDataTypeToOpenGlBaseType(GLSLDataType type)
	{
		switch (type)
		{
			case GLSLDataType::FLOAT:    return GL_FLOAT;
			case GLSLDataType::FLOAT2:   return GL_FLOAT;
			case GLSLDataType::FLOAT3:   return GL_FLOAT;
			case GLSLDataType::FLOAT4:   return GL_FLOAT;
			case GLSLDataType::MAT3:     return GL_FLOAT;
			case GLSLDataType::MAT4:     return GL_FLOAT;
			case GLSLDataType::INT:      return GL_INT;
			case GLSLDataType::INT2:     return GL_INT;
			case GLSLDataType::INT3:     return GL_INT;
			case GLSLDataType::INT4:     return GL_INT;
			case GLSLDataType::BOOL:     return GL_BOOL;
		}

		CORE_ASSERT(false, "unknown GLSLDataType");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &vaoID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &vaoID);
	}

	void OpenGLVertexArray::SetVertexBuffer(Shr<VertexBuffer>& vertexBuffer)
	{
		Bind();
		vertexBuffer->Bind();

		CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "vertex buffer has no layout");

		uint32_t index = 0;
		const BufferLayout& layout = vertexBuffer->GetLayout();
		for (const BufferElement& element : layout)
		{
			switch (element.type)
			{
				case GLSLDataType::FLOAT:
				case GLSLDataType::FLOAT2: 
				case GLSLDataType::FLOAT3: 
				case GLSLDataType::FLOAT4:
					glVertexAttribPointer(index,
						element.count,
						GLSLDataTypeToOpenGlBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.offset);
					glEnableVertexAttribArray(index);
					break;
				case GLSLDataType::INT: 
				case GLSLDataType::INT2:
				case GLSLDataType::INT3:
				case GLSLDataType::INT4:
				case GLSLDataType::BOOL:
					glVertexAttribIPointer(index,
						element.count,
						GLSLDataTypeToOpenGlBaseType(element.type),
						layout.GetStride(),
						(const void*)element.offset);
					glEnableVertexAttribArray(index);
					break;
			}
			
			index++;
		}

		this->vertexBuffer = vertexBuffer;
		Unbind();
	}

	void OpenGLVertexArray::SetElementBuffer(Shr<ElementBuffer>& elementBuffer)
	{
		Bind();
		elementBuffer->Bind();
		this->elementBuffer = elementBuffer;
		Unbind();
	}

	void OpenGLVertexArray::Bind()
	{
		if (vertexBuffer)
			vertexBuffer->Bind();
		if (elementBuffer)
			elementBuffer->Bind();
		glBindVertexArray(vaoID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
		if (vertexBuffer)
			vertexBuffer->Unbind();
		if (elementBuffer)
			elementBuffer->Unbind();
	}

}
