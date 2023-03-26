#pragma once
#include "utility.h"

#include "generic/Camera.h"
#include "renderer/FrameBuffer.h"
#include "renderer/Texture.h"
#include "utils/DataPool.h"

namespace core {
    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void ResizeWindow(uint32_t width, uint32_t height);

        static void BeginRender(const Camera& camera);
        static void EndRender();

        static void Render();

        static void DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, ProjectionMode mode, core_id coreID = -1);
        static void DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor = 1.0f, glm::vec4 color = glm::vec4(1.0f), 
            ProjectionMode mode = ProjectionMode::PERSPECTIVE, core_id coreID = -1);

        static void DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec2 texCoordSprite[4], Shr<Texture>& texture, float tilingFactor = 1.0f, glm::vec4 color = glm::vec4(1.0f),
            ProjectionMode mode = ProjectionMode::PERSPECTIVE, core_id coreID = -1);

        static void DrawTriangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, ProjectionMode mode, core_id coreID = -1);
        static void DrawTriangle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor = 1.0f, glm::vec4 color = glm::vec4(1.0f), 
            ProjectionMode mode = ProjectionMode::PERSPECTIVE, core_id coreID = -1);

        static void DrawLine(glm::vec2 position, glm::vec2 size, glm::vec4 color, float thickness, ProjectionMode mode, core_id coreID = -1);

        static void DrawCircle(glm::mat4 transform, glm::vec4 color, float rotation, float thickness, float fade, core_id coreID = -1);

        struct Stats
        {
            uint32_t drawCalls = 0;
            uint32_t objectCount = 0;
            uint32_t dataSize = 0;
            uint32_t vertexCount = 0;
            uint32_t elementCount = 0;
            uint32_t quadCount = 0;
        };
        static Stats GetStats();
        static void ClearStats();

        static Shr<Framebuffer> GetFramebuffer();

    private:

        static void StartBatch();
        static void NextBatch();

        static void DrawRectangle(glm::mat4 transform, glm::vec4 color, ProjectionMode mode, core_id coreID);
        
        static void DrawRectangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID);
        static void DrawRectangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec2 texCoordSprite[4], glm::vec4 color, ProjectionMode mode, core_id coreID);

        static void DrawTriangle(glm::mat4 transform, glm::vec4 color, ProjectionMode mode, core_id coreID);
        static void DrawTriangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID);

    };

}
