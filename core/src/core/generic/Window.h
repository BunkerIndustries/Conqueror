#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"


#include <GLFW/glfw3.h>

namespace core {
	

    struct WindowProps
    {
        std::string title;
        unsigned int width, height;

        WindowProps(std::string title = "Conqueror", unsigned int width = 1280, unsigned int height = 720)
	        : title(title), width(width), height(height) { }
    };

    class Window {
    private:
        GLFWwindow* glfw_window;
        bool initialized = false;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vsync;
            EventCallbackFunction callback;
        };

        WindowData window_data;

        Window(const WindowProps& window_props);

        void init(const WindowProps& window_props);
        void quit() const;

    public:

        ~Window();

    	static Window* createWindow(const WindowProps& window_props = WindowProps());

        unsigned int getWidth() const { return window_data.width; }
        unsigned int getHeight() const { return window_data.height; }

    	void setEventCallback(const EventCallbackFunction& callback_function) { window_data.callback = callback_function; }
        void setVSync(bool enabled);
        bool isVSync() const { return window_data.vsync; }

        GLFWwindow* getNativeWindow() const { return glfw_window; }
    };
}