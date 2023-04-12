#include "_Core.h"
#include "Input.h"

#include "event/GameEvent.h"
#include "event/MouseCodes.h"
#include "generic/Application.h"
#include "imgui/ImGuiLayer.h"
#include "renderer/Renderer.h"
#include "ui/Button.h"

#include "GLFW/glfw3.h"
#include "utils/Core.h"

namespace core
{
	bool Input::IsKeyPressed(int key_code)
	{
		auto state = glfwGetKey((GLFWwindow*)Application::GetWindow()->GetNativeWindow(), key_code);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto state = glfwGetMouseButton((GLFWwindow*)Application::GetWindow()->GetNativeWindow(), button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousPos()
	{
		double posX, posY;
		glfwGetCursorPos((GLFWwindow*)Application::GetWindow()->GetNativeWindow(), &posX, &posY);
		return glm::vec2(posX, posY);
	}

	void Input::ProcessInput()
	{
        //mouse picking;
        glm::ivec2 pos = glm::ivec2(-1, -1);

        if (!Application::GetImGuiEnabled())
        {
            glm::vec2 mousePos = Input::GetMousPos();

            mousePos.y = Application::GetWindow()->GetHeight() - mousePos.y;
            if (mousePos.x < Application::GetWindow()->GetWidth() && mousePos.y < Application::GetWindow()->GetHeight())
            {
                pos = mousePos;
            }

        }
        else if (Application::GetImGuiLayer().IsMouseInsideViewport())
        {
            pos = Application::GetImGuiLayer().GetMousePosViewportRelative();
        }

        if (pos.x >= 0 && pos.y >= 0 && !Application::GetImGuiSwitched() && !Application::IsResizing()) {
            Renderer::GetFramebuffer()->Bind();
            mouseHoverID[0] = Renderer::GetFramebuffer()->ReadPixel(1, pos);
            Renderer::GetFramebuffer()->Unbind();
        }
        if (Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouseClickedID[0] = mouseHoverID[0];
            if (mouseClickedID[0] != mouseClickedID[1] && mouseClickedID[0] != 0 && !pressed)
            {
                GameObject* gameObject = dynamic_cast<GameObject*>(Core::GetObjectByID(mouseClickedID[0]));
                if (gameObject)
					Application::QueueEvents(new GameObjectPressedEvent(gameObject));

                Button* button = dynamic_cast<Button*>(Core::GetObjectByID(mouseClickedID[0]));
                if (button)
                    button->buttonEventFunction();
            }
            pressed = true;
            mouseClickedID[1] = mouseClickedID[0];
        }
        else {
            pressed = false;
            if (mouseClickedID[1] != 0) {
                GameObject* gameObject = dynamic_cast<GameObject*>(Core::GetObjectByID(mouseClickedID[1]));
                if (gameObject)
					Application::QueueEvents(new GameObjectReleasedEvent(gameObject));
            }


            mouseClickedID[1] = 0;
            if (mouseHoverID[0] != mouseHoverID[1])
            {
                if (mouseHoverID[1] != 0) {
                    GameObject* gameObject = dynamic_cast<GameObject*>(Core::GetObjectByID(mouseHoverID[1]));
                    if (gameObject)
						Application::QueueEvents(new GameObjectHoverEndEvent(gameObject));
                }
                if (mouseHoverID[0] != 0) {
                    GameObject* gameObject = dynamic_cast<GameObject*>(Core::GetObjectByID(mouseHoverID[0]));
                    if (gameObject)
						Application::QueueEvents(new GameObjectHoverBeginEvent(gameObject));
                }
            }
            mouseHoverID[1] = mouseHoverID[0];
        }
	}
}
