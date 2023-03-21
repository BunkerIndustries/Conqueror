#pragma once
#include "_Core.h"
#include "utility.h"

namespace  core
{
	enum class GLSLDataType
	{
		NONE,
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		INT, INT2, INT3, INT4,
		MAT3, MAT4,
		BOOL
	};

	static int GetDataTypeSizeBytes(GLSLDataType type)
	{
		switch (type)
		{
			case GLSLDataType::FLOAT:   return 4 * 1;
			case GLSLDataType::FLOAT2:  return 4 * 2;
			case GLSLDataType::FLOAT3:  return 4 * 3;
			case GLSLDataType::FLOAT4:  return 4 * 4;
			case GLSLDataType::INT:		return 4 * 1;
			case GLSLDataType::INT2:	return 4 * 2;
			case GLSLDataType::INT3:	return 4 * 3;
			case GLSLDataType::INT4:	return 4 * 4;
			case GLSLDataType::MAT3:	return 4 * 3 * 3;
			case GLSLDataType::MAT4:	return 4 * 4 * 4;
			case GLSLDataType::BOOL:	return 1;
		}

		CORE_ASSERT(false, "unknown GLSLDataType");
		return 0;
	}

	// vbo variable type
	// e.g: position, color, textureID, textureCoords, ...
	struct BufferElement
	{
		std::string name;
		GLSLDataType type;
		uint32_t size;
		uint32_t count;
		size_t offset;
		bool normalized;

		BufferElement() = default;

		BufferElement(GLSLDataType type, std::string name, bool normalized = false)
			: name(name), type(type), size(GetDataTypeSizeBytes(type)), count(GetDataTypeCount()), offset(0), normalized(normalized) { }

	private:

		int GetDataTypeCount() const
		{
			switch (type)
			{
			case GLSLDataType::FLOAT:   return 1;
			case GLSLDataType::FLOAT2:  return 2;
			case GLSLDataType::FLOAT3:  return 3;
			case GLSLDataType::FLOAT4:  return 4;
			case GLSLDataType::INT:		return 1;
			case GLSLDataType::INT2:	return 2;
			case GLSLDataType::INT3:	return 3;
			case GLSLDataType::INT4:	return 4;
			case GLSLDataType::MAT3:	return 3;
			case GLSLDataType::MAT4:	return 4;
			case GLSLDataType::BOOL:	return 1;
			default:;
			}

			CORE_ASSERT(false, "unknown GLSLDataType");
			return 0;
		}
	};

	// buffer element combination
	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:elements(elements)
		{
			CalculateData();
		}

		uint32_t GetStride() const { return stride; }
		uint32_t GetSize() const { return size; }
		std::vector<BufferElement> GetElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

	private:
		std::vector<BufferElement> elements;

		uint32_t stride = 0;
		uint32_t size = 0;
		void CalculateData()
		{
			size_t offset = 0;
			stride = 0;
			size = 0;
			for (auto& element : elements)
			{
				element.offset = offset;
				offset += element.size;
				stride += element.size;
				size += element.count;
			}
		}
	};
	
	class VertexBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() = 0;

		virtual ~VertexBuffer() = default;

		static Shr<VertexBuffer> CreateBuffer(BufferLayout& layout, uint32_t size);
	};

	class ElementBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetElementCount() = 0;

		virtual ~ElementBuffer() = default;

		static Shr<ElementBuffer> CreateBuffer(uint32_t* data, uint32_t count);
	};
}
