#include "_Core.h"
#include "OpenGLTexture.h"

#include "renderer/Texture.h"

#include <glad/glad.h>
#include <STB_IMAGE/stb_image.h>


namespace core
{
	OpenGLTexture::OpenGLTexture(std::string filePath, std::string name)
	{
		this->filePath = filePath;
		this->name = name;

		if (!Init(this->filePath))
		{
			glDeleteTextures(1, &texID);
			Init("assets/textures/error_texture_256x256.png");
		}
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &texID);
	}

	void OpenGLTexture::Bind(unsigned slot)
	{
		if (slot < 32)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, texID);
			return;
		}
		LOG_CORE_WARN("You should not go over 32 texture slots, as the OpenGL specification does not allow more");
	}

	void OpenGLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint32_t OpenGLTexture::GetID() const
	{
		return this->texID;
	}

	int OpenGLTexture::GetWidth()
	{
		return this->width;
	}

	int OpenGLTexture::GetHeight()
	{
		return this->height;
	}

	bool OpenGLTexture::operator==(const Texture& other) const
	{
		return texID == other.GetID();
	}

	std::string OpenGLTexture::GetFilePath()
	{
		return this->filePath;
	}

	std::string OpenGLTexture::GetName()
	{
		return this->name;
	}

	bool OpenGLTexture::Init(std::string path)
	{
		glGenTextures(1, &texID);
		// use texture (everything that is called from now will be set to the current texture)
		glBindTexture(GL_TEXTURE_2D, texID);
		// set texture parameters

		// repeat image in both directions (activate the repeating of the texture)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// pixelate the texture when made bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// pixelate the texture when made smaller
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(true);
		// load texture and save formats to the variables (4 == RGBA format)
		localBuffer = stbi_load(path.c_str(), &width, &height, &channels, 0);

		// free memory if path is invalid
		if (localBuffer)
		{
			if (channels == 3) {
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
			}
			else if (channels == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
			}
			else {
				LOG_CORE_ERROR("Unknown number of channel '" + std::to_string(channels) + "' by texture '" + path + "'");
				return false;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			LOG_CORE_ERROR("Could not load image '" + path + "'");
			return false;
		}

		stbi_image_free(localBuffer);
		return true;
	}
}
