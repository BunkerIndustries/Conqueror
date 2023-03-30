#include "_Core.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace core
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         LOG_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       LOG_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          LOG_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_CORE_TRACE(message); return;
		}

		CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRenderAPI::Init()
	{
#ifdef BUILD_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRenderAPI::SetClearColor(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::DrawElements(Shr<VertexArray>& vertexArray, uint32_t elementCount)
	{
		vertexArray->Bind();
		uint32_t count = elementCount ? elementCount : vertexArray->GetElementBuffer()->GetElementCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		vertexArray->Unbind();
	}
	
	void OpenGLRenderAPI::DrawLines(Shr<VertexArray>& vertexArray, uint32_t vertexCount, float thickness)
	{
		vertexArray->Bind();
		SetLineWidth(thickness);
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
	
	void OpenGLRenderAPI::SetLineWidth(float thickness)
	{
		glLineWidth(thickness);
	}

	void OpenGLRenderAPI::DrawIndexed(const Shr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetElementBuffer()->GetElementCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
