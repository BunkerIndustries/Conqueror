#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/Texture.h"

namespace core
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(std::string filePath, std::string name);
		~OpenGLTexture() override;

		void Bind(unsigned slot) override;
		void Unbind() override;

		uint32_t GetID() const override;
		int GetWidth() override;
		int GetHeight() override;

		bool operator==(const Texture& other) const override;

		std::string GetFilePath() override;
		std::string GetName() override;

	private:
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