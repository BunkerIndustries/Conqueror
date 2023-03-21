#pragma once
#include "_Core.h"
#include "utility.h"

namespace core
{
	class Context
	{
	public:
		virtual ~Context() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void SwapBuffer() = 0;

		static Shr<Context> CreateContext(void* window);
	};
}

