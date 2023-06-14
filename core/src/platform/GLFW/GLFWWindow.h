#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Window.h"
#include "renderer/Context.h"

#include <GLFW/glfw3.h>

namespace core
{
	class GLFWWindow : public Window
	{
	public:

		GLFWWindow(const WindowProps& window_props);
		~GLFWWindow() override;

		void PollEvents() override;
		void SwapBuffers() override;

		unsigned int GetWidth() const override { return windowData.width; }
		unsigned int GetHeight() const override { return windowData.height; }

		float GetTime() const override;

		void Resize(unsigned width, unsigned height) override;

		void SetEventCallback(const EventCallbackFunction& callback_function) override { windowData.callback = callback_function; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return windowData.vsync; }

		void EnableFullscreen(bool enabled) override;

		void* GetNativeWindow() const override { return glfwWindow; }

	private:
		GLFWwindow* glfwWindow;
		Shr<Context> context;

		glm::vec2 lastWindowSize;

		bool fullscreenEnabled = false;

		bool initialized = false;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vsync;
			EventCallbackFunction callback;
		};

		WindowData windowData;


		void Init(const WindowProps& window_props);
		void Quit() const;
	};
	
}

