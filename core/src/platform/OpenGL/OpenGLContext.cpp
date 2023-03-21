#include "_Core.h"
#include "OpenGLContext.h"

#include "generic/Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace core
{
	OpenGLContext::OpenGLContext(void* window)
		: window(window) { }

	void OpenGLContext::Init()
	{
		int status = 0;
		switch (Window::GetFramework())
		{
			case Window::GLFW:
				glfwMakeContextCurrent((GLFWwindow*)window);
				status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
				CORE_ASSERT(status, "Failed to initialize Glad!");
				break;
		
			default: 
				CORE_ASSERT(false, "NONE is a not valid framework");
				break;
		}

		LOG_CORE_TRACE("OpenGL driver:");
		LOG_CORE_TRACE("\tCompany: {0}", (const char*)glGetString(GL_VENDOR));
		LOG_CORE_TRACE("\tRenderer: {0}", (const char*)glGetString(GL_RENDERER));
		LOG_CORE_TRACE("\tVersion: {0}", (const char*)glGetString(GL_VERSION));
		
		CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "OpenGL version is not >= 4.5!");
	}

	void OpenGLContext::SwapBuffer()
	{
		switch (Window::GetFramework())
		{
			case Window::GLFW:
				glfwSwapBuffers((GLFWwindow*)window);
				break;

			default:
				CORE_ASSERT(false, "NONE is a not valid framework");
				break;
		}
		
	}
}
