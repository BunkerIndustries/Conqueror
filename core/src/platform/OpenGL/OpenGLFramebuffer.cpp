#include "_Core.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace core {

	static bool IsDepthFormat(FramebufferTexFormat format)
	{
		switch (format)
		{
		case FramebufferTexFormat::DEPTH24STECIL8:
			return true;
		default:;
		}
		return false;
	}

	static GLenum TextureTarget(bool multisampled)
	{
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
	{
		glCreateTextures(TextureTarget(multisampled), count, outID);
	}

	static void BindTexture(bool multisampled, uint32_t id)
	{
		glBindTexture(TextureTarget(multisampled), id);
	}

	static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, size_t index)
	{
		bool multisample = samples > 1;
		if (multisample)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisample), id, 0);
	}

	static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
	{
		bool multisample = samples > 1;
		if (multisample)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisample), id, 0);
	}

	static GLenum FBTexFormatToGL(FramebufferTexFormat format)
	{
		switch (format) {
		case FramebufferTexFormat::RGBA8: return GL_RGBA8;
		case FramebufferTexFormat::RED_INTEGER: return GL_RED_INTEGER;
		default:;
		}

		CORE_ASSERT(false, "");
		return 0;
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
		:specification(specification)
	{
		for (auto format : specification.attachment.attachments)
		{
			if (!IsDepthFormat(format.texFormat))
			{
				colorAttachmentSpec.emplace_back(format);
			} 
			else
			{
				depthAttachmentSpec = format;
			}
		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer() {
		glDeleteFramebuffers(1, &fboID);
		glDeleteTextures(colorAttachmentsID.size(), colorAttachmentsID.data());
		glDeleteTextures(1, &depthAttachmentID);
	}

	void OpenGLFramebuffer::Invalidate() {
		if (fboID)
		{
			glDeleteFramebuffers(1, &fboID);
			glDeleteTextures(colorAttachmentsID.size(), colorAttachmentsID.data());
			glDeleteTextures(1, &depthAttachmentID);
			colorAttachmentsID.clear();
			depthAttachmentID = 0;
		}
		glCreateFramebuffers(1, &fboID);
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
		bool multisample = specification.samples > 1;
		//color
		if (colorAttachmentSpec.size())
		{
			colorAttachmentsID.resize(colorAttachmentSpec.size());
			CreateTextures(multisample, colorAttachmentsID.data(), colorAttachmentsID.size());
			for (size_t i = 0; i < colorAttachmentsID.size(); i++)
			{
				BindTexture(multisample, colorAttachmentsID[i]);
				switch (colorAttachmentSpec[i].texFormat)
				{
				case FramebufferTexFormat::RGBA8:
					AttachColorTexture(colorAttachmentsID[i], specification.samples, GL_RGBA8, GL_RGBA, specification.width, specification.height, i);
					break;
				case FramebufferTexFormat::RED_INTEGER:
					AttachColorTexture(colorAttachmentsID[i], specification.samples, GL_R32I, GL_RED_INTEGER, specification.width, specification.height, i);
					break;
				}
			}
		}
		//depth
		if (depthAttachmentSpec.texFormat != FramebufferTexFormat::None)
		{
			CreateTextures(multisample, &depthAttachmentID, 1);
			BindTexture(multisample, depthAttachmentID);
			switch (depthAttachmentSpec.texFormat)
			{
			case FramebufferTexFormat::DEPTH24STECIL8:
				AttachDepthTexture(depthAttachmentID, specification.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, specification.width, specification.height);
				break;
			}
		}
		if (colorAttachmentsID.size() > 1)
		{
			CORE_ASSERT(colorAttachmentsID.size() <= 4, "");
			GLenum buffer[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(colorAttachmentsID.size(), buffer);
		}
		else if (colorAttachmentsID.empty())
		{
			// only depth
			glDrawBuffer(GL_NONE);
		}
		CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(unsigned int width, unsigned int height)
	{
		specification.width = width;
		specification.height = height;
		Invalidate();
		Bind();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, glm::ivec2 pos)
	{
		CORE_ASSERT(attachmentIndex < colorAttachmentsID.size(), "");
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(pos.x, pos.y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		CORE_ASSERT(attachmentIndex < colorAttachmentsID.size(), "");

		auto& spec = colorAttachmentSpec[attachmentIndex];

		glClearTexImage(colorAttachmentsID[attachmentIndex], 0, FBTexFormatToGL(spec.texFormat), GL_UNSIGNED_INT, &value);
	}

	void OpenGLFramebuffer::ProjectToScreen(uint32_t attachmentIndex, uint32_t width, uint32_t height)
	{
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, fboID);
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		//glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		//glBlitFramebuffer(0, 0, specification.width, specification.height, 0, 0, width, height,
		//	GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLFramebuffer::SetViewPort()
	{
		glViewport(0, 0, specification.width, specification.height);
	}

	void OpenGLFramebuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	}

	void OpenGLFramebuffer::Unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::BindAttachmentAsTexture(uint32_t attachment, uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, GetColorID(attachment));
	}
}
