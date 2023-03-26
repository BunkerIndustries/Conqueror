#include "_Core.h"

#include "component/CircleRenderer.h"
#include "generic/GameObject.h"
#include "renderer/Texture.h"
#include "utils/DataPool.h"
#include "utils/Utils.h"
#include "renderer/RenderCommand.h"
#include "renderer/Renderer.h"

#include "imgui/ImGuiLayer.h"

namespace core {

    CircleRenderer::CircleRenderer(glm::vec2 position, glm::vec2 size, glm::vec4 color, float rotation, float thickness, float fade)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        this->transform = transform;
        this->color = color;
        this->thickness = thickness;
        this->fade = fade;
        this->rotation = rotation;
    }

    void CircleRenderer::OnUpdate() 
    {
        Renderer::DrawCircle(transform, color, rotation, thickness, fade);
    }

    void CircleRenderer::OnImgui(float dt)
    {

    }

}