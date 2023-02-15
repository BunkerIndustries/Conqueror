#include "_Core.h"
#include "utility.h"

#include "generic/Window.h"
#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"

#include <GLAD/glad.h>

namespace core {

    static void errorCallback(int error, const char* description)
    {
        CORE_ASSERT("GLFW ERROR {0}: {1}", error, description);
    }

    Window::Window(const WindowProps& window_props)
    {
        init(window_props);
    }

    Window::~Window()
    {
        quit();
    }

    void Window::init(const WindowProps& window_props)
    {
        window_data.title = window_props.title;
        window_data.width = window_props.width;
        window_data.height = window_props.height;

        LOG_CORE_TRACE("Creating window {0} ({1}, {2})", window_props.title, window_props.width, window_props.height);

        if (!initialized)
        {
	        int const success = glfwInit();
	        CORE_ASSERT(success, "Could not init GLFW.");
	        glfwSetErrorCallback(errorCallback);
            initialized = true;
        }

        glfw_window = glfwCreateWindow(window_props.width, window_props.height, window_props.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(glfw_window);
        glfwSetWindowUserPointer(glfw_window, &window_data);
        setVSync(true);

        int const success = gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
        CORE_ASSERT(success, "Could not init glad!");

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        //callbacks
        glfwSetWindowSizeCallback(glfw_window, [](GLFWwindow* window, int width, int height)
        {
        	WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.callback(event);
        });

        glfwSetWindowCloseCallback(glfw_window, [](GLFWwindow* window)
        {
        	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.callback(event);
        });

        glfwSetKeyCallback(glfw_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
        	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

	        switch (action)
	        {
	            case GLFW_PRESS:
                {
	            	KeyPressedEvent event(key, 0);
	            	data.callback(event);
	            	break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.callback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.callback(event);
                    break;
                }
                default:;
            }
        });

        glfwSetCharCallback(glfw_window, [](GLFWwindow* window, unsigned int key_code)
        {
        	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(key_code);
            data.callback(event);
	    });

        glfwSetMouseButtonCallback(glfw_window, [](GLFWwindow* window, int button, int action, int mods)
        {
        	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.callback(event);
                    break;
                }
                default:;
            }
        });

        glfwSetScrollCallback(glfw_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
        	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.callback(event);
        });

        glfwSetCursorPosCallback(glfw_window, [](GLFWwindow* window, double xPos, double yPos)
        {
        	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        	MouseMovedEvent event((float)xPos, (float)yPos);
			data.callback(event);
        });
    }

    void Window::quit() const
    {
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }

    void Window::setVSync(const bool enabled)
    {
        glfwSwapInterval(enabled);
        window_data.vsync = enabled;
    }

    Window* Window::createWindow(const WindowProps& window_props)
    {
        return new Window(window_props);
    }

}