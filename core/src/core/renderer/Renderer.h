#pragma once
#include "utility.h"

#include "generic/Camera.h"
#include "generic/Transform.h"
#include "renderer/FrameBuffer.h"
#include "renderer/Texture.h"
#include "utils/DataPool.h"

#include "renderer/Font.h"

#define DEFAULT_COLOR glm::vec4(0.925f, 0.329f, 0.956, 1.0f)

namespace core {

    struct EdgeRenderData
    {
        Transform transform = Transform();
        glm::vec4 color = DEFAULT_COLOR;

        Shr<Texture> texture = nullptr;
        glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        float tilingFactor = 1.0f;

        ProjectionMode mode = ProjectionMode::PERSPECTIVE;
        core_id coreID = 0;
        core_id uiID = -1;
    };

    struct CircleRenderData
    {
        Transform transform = Transform();
        glm::vec4 color = DEFAULT_COLOR;

        float thickness = 1.0f;
        float fade = 0.005f;

        Shr<Texture> texture = nullptr;
        glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        float tilingFactor = 1.0f;

        ProjectionMode mode = ProjectionMode::PERSPECTIVE;
        core_id coreID = 0;
        core_id uiID = -1;
    };

    struct LineRenderData
    {
        glm::vec2 point0 = glm::vec2(0.0f, 0.0f);
        glm::vec2 point1 = glm::vec2(1.0f, 0.0f);
        glm::vec4 color = DEFAULT_COLOR;

        float thickness = 1.0f;

        ProjectionMode mode = ProjectionMode::PERSPECTIVE;
        core_id coreID = 0;
        core_id uiID = -1;
    };

    struct TextRenderData
    {
        Transform transform = Transform();
        glm::vec4 color = DEFAULT_COLOR;

        std::string string = "";
        Shr<Font> font = DataPool::GetFont("mononoki.ttf");

        ProjectionMode mode = ProjectionMode::PERSPECTIVE;
        core_id coreID = 0;
        core_id uiID = -1;
    };

    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void ResizeWindow(uint32_t width, uint32_t height);

        static void BeginRender(const Camera& camera);
        static void EndRender();

        static void Render();

        static void DrawRectangle(const EdgeRenderData& renderData);

        static void DrawTriangle(const EdgeRenderData& renderData);

        static void DrawLine(const LineRenderData& renderData);

        static void DrawCircle(const CircleRenderData& renderData);

        static void DrawString(const TextRenderData& renderData);

        struct Stats
        {
            uint32_t drawCalls = 0;
            uint32_t objectCount = 0;
            uint32_t dataSize = 0;
            uint32_t vertexCount = 0;
            uint32_t elementCount = 0;
        };
        static Stats GetStats();
        static void ClearStats();

        static Shr<Framebuffer> GetFramebuffer();

        static void NextBatch();
    private:

        static void StartBatch();
    };

}
