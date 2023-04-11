#include "_Core.h"

#include "component/CircleRenderer.h"
#include "generic/GameObject.h"
#include "renderer/Renderer.h"


namespace core {

    CircleRenderer::CircleRenderer(glm::vec4 color, float thickness, float fade)
	    : color(color), texture(nullptr), thickness(thickness), fade(fade) { }

    CircleRenderer::CircleRenderer(glm::vec4 color, Shr<Texture> texture, float thickness, float fade)
        : color(color), texture(texture), thickness(thickness), fade(fade) { }

    void CircleRenderer::OnUpdate() 
    {
        if (texture)
            Renderer::DrawCircle(gameObject->transform.position, gameObject->transform.scale, gameObject->transform.rotation, texture, 1.0f, color, thickness, fade, gameObject->GetProjectionMode(), gameObject->GetObjectID());
        else
			Renderer::DrawCircle(gameObject->transform.position, gameObject->transform.scale, gameObject->transform.rotation, color, thickness, fade, gameObject->GetProjectionMode(), gameObject->GetObjectID());
    }
}