#pragma once
#include "_Core.h"
#include "utility.h"

#include "renderer/Context.h"

namespace core {
	class OpenGLContext : public Context
	{
	public:
		explicit OpenGLContext(void* window);
		~OpenGLContext() override = default;

		void Init() override;
		void Shutdown() override { };

		void SwapBuffer() override;

	private:
		void* window;
	};
}

