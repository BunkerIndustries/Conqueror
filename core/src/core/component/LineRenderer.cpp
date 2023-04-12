#include "_Core.h"
#include "utility.h"
#include "LineRenderer.h"
#include "renderer/Renderer.h"
#include "layer/Layer.h"
#include "Engine.h"

namespace core
{
	LineRenderer::LineRenderer(glm::vec2 positionA, glm::vec2 positionB, glm::vec4 color, float thickness, float lastingTime)
		:positionA(positionA), positionB(positionB), color(color), thickness(thickness), lastingTime(lastingTime) { }

	void LineRenderer::OnUpdate()
	{
		dt_counter += Application::GetDT();
		Renderer::DrawLine(positionA, positionB, color, thickness, gameObject->GetProjectionMode(), gameObject->GetCoreID());

		if (dt_counter >= lastingTime) delete gameObject;
	}
};