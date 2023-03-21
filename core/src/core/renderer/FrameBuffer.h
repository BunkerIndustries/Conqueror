#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {


	enum class FramebufferTexFormat
	{
		None = 0,

		//COLORS
		RGBA8,
		RED_INTEGER,

		//DEPTH
		DEPTH24STECIL8,

		//DEFAULT
		Depth = DEPTH24STECIL8
	};

	struct FramebufferTexSpecification 
	{
		FramebufferTexSpecification() = default;
		FramebufferTexSpecification(FramebufferTexFormat format)
			: texFormat(format) { };

		FramebufferTexFormat texFormat = FramebufferTexFormat::None;
	};

	struct FramebufferAttachSpecification 
	{
		FramebufferAttachSpecification() = default;
		FramebufferAttachSpecification(std::initializer_list<FramebufferTexSpecification> attachments) 
			: attachments(attachments) { }

		std::vector<FramebufferTexSpecification> attachments;
	};

	struct FramebufferSpecification 
	{
		FramebufferAttachSpecification attachment;

		uint32_t width, height;
		uint32_t samples = 1;
	};

	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual uint32_t GetColorID(uint32_t index = 0) = 0; 

		virtual void Invalidate() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual int ReadPixel(uint32_t attachmentIndex, glm::ivec2 pos) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
		virtual void ProjectToScreen(uint32_t attachmentIndex, uint32_t width, uint32_t height) = 0;

		virtual void SetViewPort() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual FramebufferSpecification& GetSpecification() = 0;
		static Shr<Framebuffer> CreateBuffer(const FramebufferSpecification& specification);
	};
}