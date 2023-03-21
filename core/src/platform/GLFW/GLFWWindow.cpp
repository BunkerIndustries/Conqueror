#include "_Core.h"
#include "GLFWWindow.h"

#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"


#include <glfw/glfw3.h>


namespace core
{
    static void errorCallback(int error, const char* description)
    {
        CORE_ASSERT("GLFW ERROR {0}: {1}", error, description);
    }

    GLFWWindow::GLFWWindow(const WindowProps& window_props)
    {
        Init(window_props);
    }

    GLFWWindow::~GLFWWindow()
    {
        context->Shutdown();
        Quit();
    }

    void GLFWWindow::PollEvents()
    {
        glfwPollEvents();
    }

    void GLFWWindow::SwapBuffers()
    {
        context->SwapBuffer();
    }

    void GLFWWindow::Init(const WindowProps& window_props)
    {
        windowData.title = window_props.title;
        windowData.width = window_props.width;
        windowData.height = window_props.height;

        LOG_CORE_TRACE("Creating window {0} ({1}, {2})", window_props.title, window_props.width, window_props.height);

        if (!initialized)
        {
            int const success = glfwInit();
            CORE_ASSERT(success, "Could not init GLFW.");
            glfwSetErrorCallback(errorCallback);
            initialized = true;
        }

        glfwWindow = glfwCreateWindow(window_props.width, window_props.height, window_props.title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(glfwWindow, &windowData);
        SetVSync(true);

        context = Context::CreateContext(glfwWindow);
        context->Init();

        //callbacks
        glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.callback(event);
            });

        glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.callback(event);
            });

        glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS:
        {
            KeyPressedEvent event(key, false, mods);
            data.callback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            KeyReleasedEvent event(key, mods);
            data.callback(event);
            break;
        }
        case GLFW_REPEAT:
        {
            KeyPressedEvent event(key, true, mods);
            data.callback(event);
            break;
        }
        default:;
        }
            });

        glfwSetCharCallback(glfwWindow, [](GLFWwindow* window, unsigned int key_code)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(key_code);
        data.callback(event);
            });

        glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS:
        {
            MouseButtonPressedEvent event(button, mods);
            data.callback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            MouseButtonReleasedEvent event(button, mods);
            data.callback(event);
            break;
        }
        default:;
        }
            });

        glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.callback(event);
            });

        glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.callback(event);
            });
    }

    void GLFWWindow::Quit() const
    {
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    float GLFWWindow::GetTime() const
    {
        return (float)glfwGetTime();
    }

    void GLFWWindow::SetVSync(const bool enabled)
    {
        glfwSwapInterval(enabled);
        windowData.vsync = enabled;
    }
}