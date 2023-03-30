#include "_Core.h"
#include "utility.h"
#include "LineRenderer.h"
#include "renderer/Renderer.h"
#include "layer/Layer.h"
#include "Engine.h"

namespace core
{
	LineRenderer::LineRenderer(glm::vec2 positionA, glm::vec2 positionB, glm::vec4 color, float thickness, float lasting_time)
	{
		Init(positionA, positionB, color, thickness, lasting_time);
	}

	void LineRenderer::Init(glm::vec2 positionA, glm::vec2 positionB, glm::vec4 color, float thickness, float lasting_time)
	{
		this->positionA = positionA;
		this->positionB = positionB;
		this->color = color;
		this->thickness = thickness;
		this->lasting_time = lasting_time;
		this->dt_counter = 0.0f;
	}

	void LineRenderer::OnUpdate()
	{
		dt_counter += Application::GetDT();
		Renderer::DrawLine(positionA, positionB, color, thickness, gameObject->GetProjectionMode(), gameObject->GetObjectID());

		if (dt_counter >= lasting_time) delete gameObject;
	}

	void LineRenderer::OnImgui(float dt)
	{

	}
};