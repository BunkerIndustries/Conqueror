#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {

	class Input
	{
	public:
		static bool IsKeyPressed(int key_code);
		static bool IsMouseButtonPressed(int button);
		static glm::vec2 GetMousPos();
	};

}
