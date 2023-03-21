#include "_Core.h"
#include "utility.h"
#include "generic/Window.h"

#include "GLFW/GLFWWindow.h"

namespace core {

    Window::FRAMEWORK Window::framework = Window::GLFW;

    Shr<Window> Window::Create(const WindowProps& windowProps)
    {
	    switch (Window::GetFramework())
	    {
            case NONE: CORE_ASSERT(false, "NONE is a not valid framework"); return nullptr;
	        case GLFW: return MakeShr<GLFWWindow>(windowProps);
	    }

        CORE_ASSERT(false, "ONLY WINDOWS IS CURRENTLY SUPPORTED!")
        return nullptr;
    }
}
