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

	
	class FrameBuffer
	{
	private:
		FramebufferSpecification specification;
		unsigned int fboID = 0;

		std::vector<FramebufferTexSpecification> colorAttachmentSpec; // color specifications
		FramebufferTexSpecification depthAttachmentSpec = FramebufferTexFormat::None; //depth specification
		
		std::vector<uint32_t> colorAttachmentsID; // texture id's
		uint32_t depthAttachmentID;

	public:
		FrameBuffer(const FramebufferSpecification& specification);
		~FrameBuffer();

		uint32_t GetColorID(uint32_t index = 0) const { CORE_ASSERT(index < colorAttachmentsID.size(), ""); return colorAttachmentsID[index]; }

		void Invalidate();
		void Resize(unsigned int width, unsigned int height);
		int ReadPixel(uint32_t attachmentIndex, glm::ivec2 pos);

		void ClearAttachment(uint32_t attachmentIndex, int value);

		void Bind();
		void Unbind();

		FramebufferSpecification& GetProperties() { return specification; }
	};
}


