#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/Texture.h"

#include "glad/glad.h"

namespace core
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(std::string filePath, std::string name);
		OpenGLTexture(TextureSpecification specification);
		~OpenGLTexture() override;

		void Bind(unsigned slot) override;
		void Unbind() override;

		void SetData(void* data, uint32_t size) override;

		bool IsLoaded() override;

		uint32_t GetID() const override;
		int GetWidth() override;
		int GetHeight() override;

		bool operator==(const Texture& other) const override;

		std::string GetFilePath() override;
		std::string GetName() override;

	private:
		TextureSpecification specification;

		GLenum internalFormat;
		GLenum dataFormat;

		std::string filePath;
		std::string name;

		unsigned char* localBuffer;

		int width;
		int height;
		int channels;

		uint32_t texID;

		bool Init(std::string path);
	};
}