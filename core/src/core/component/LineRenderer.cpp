#include "_Core.h"
#include "utility.h"
#include "LineRenderer.h"
#include "renderer/Renderer.h"
#include "layer/Layer.h"
#include "Engine.h"

namespace core
{
	LineRenderer::LineRenderer(glm::vec2 positionA, glm::vec2 positionB, glm::vec4 color, float thickness)
		:positionA(positionA), positionB(positionB), color(color), thickness(thickness) { }

	void LineRenderer::OnUpdate()
	{
		dt_counter += Application::GetDT();
		Renderer::DrawLine(positionA, positionB, color, thickness, gameObject->GetProjectionMode(), gameObject->GetObjectID());

		if (dt_counter >= lasting_time) delete gameObject;
	}
};