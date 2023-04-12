#pragma once
#include "_Core.h"
#include "utility.h"

#include "core/renderer/Framebuffer.h"

namespace core
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		
		OpenGLFramebuffer(const FramebufferSpecification& specification);
		~OpenGLFramebuffer() override;

		void Invalidate() override;
		void Resize(unsigned width, unsigned height) override;

		int ReadPixel(uint32_t attachmentIndex, glm::ivec2 pos) override;

		void ClearAttachment(uint32_t attachmentIndex, int value) override;
		void ProjectToScreen(uint32_t attachmentIndex, uint32_t width, uint32_t height) override;

		void SetViewPort() override;
		void Bind() override;
		void Unbind() override;

		void BindAttachmentAsTexture(uint32_t attachment, uint32_t slot) override;

		FramebufferSpecification& GetSpecification() override { return specification; }
		uint32_t GetColorID(uint32_t index) override
		{
			CORE_ASSERT(index < colorAttachmentsID.size(), "");
			return colorAttachmentsID[index];
		}

	private:
		FramebufferSpecification specification;
		unsigned int fboID = 0;

		std::vector<FramebufferTexSpecification> colorAttachmentSpec; // color specifications
		FramebufferTexSpecification depthAttachmentSpec = FramebufferTexFormat::None; //depth specification

		std::vector<uint32_t> colorAttachmentsID; // texture id's
		uint32_t depthAttachmentID;
	};
}
