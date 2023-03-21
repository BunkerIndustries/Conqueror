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

	private:
		friend class Application;

		inline static int mouseHoverID[2] = { 0, 0 };
		inline static int mouseClickedID[2] = { 0, 0 };
		inline static bool pressed = false;

		static void ProcessInput();
	};

}
