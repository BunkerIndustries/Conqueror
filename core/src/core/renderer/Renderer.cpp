#include "_Core.h"

#include "renderer/Renderer.h"
#include "renderer/RenderCommand.h"
#include "utils/DataPool.h"
#include "renderer/Shader.h"
#include "generic/Application.h"

namespace core {

    struct RectangleVertex
    {
        glm::vec2 position;
        glm::vec4 color;
        glm::vec2 texCoords;
        float tilingFactor;
        int texIndex;
        int projectionMode;
        int coreID;
    };

    struct TriangleVertex
    {
        glm::vec2 position;
        glm::vec4 color;
        glm::vec2 texCoords;
        float tilingFactor;
        int texIndex;
        int projectionMode;
        int coreID;
    };

    struct LineVertex
    {
        glm::vec2 position;
        glm::vec4 color;
        int projectionMode;
        int coreID;
    };

    struct RenderData
    {
        static constexpr uint32_t MAX_VERTICES = 40000;
        static constexpr uint32_t MAX_ELEMENTS = 60000;
        static constexpr uint32_t MAX_TEXTURE_SLOTS = 32;

        Shr<Shader> edgeGeometryShader;

        Shr<Shader> lineGeometryShader;

        Shr<VertexArray> rectangleVertexArray;
        Shr<VertexBuffer> rectangleVertexBuffer;

        Shr<VertexArray> lineVertexArray;
        Shr<VertexBuffer> lineVertexBuffer;

        Shr<VertexArray> triangleVertexArray;
        Shr<VertexBuffer> triangleVertexBuffer;

        uint32_t rectangleElementCount = 0;
        RectangleVertex* rectangleVertexBufferBase = nullptr;
        RectangleVertex* rectangleVertexBufferPtr = nullptr;

        uint32_t triangleElementCount = 0;
        TriangleVertex* triangleVertexBufferBase = nullptr;
        TriangleVertex* triangleVertexBufferPtr = nullptr;

        uint32_t lineElementCount = 0;
        LineVertex* lineVertexBufferBase = nullptr;
        LineVertex* lineVertexBufferPtr = nullptr;

        std::array<Shr<Texture>, MAX_TEXTURE_SLOTS> rectangleTextureSlots;
        uint32_t rectangleTextureSlotIndex = 0;

        std::array<Shr<Texture>, MAX_TEXTURE_SLOTS> triangleTextureSlots;
        uint32_t triangleTextureSlotIndex = 0;

        Camera camera;

        float lineWidth = 1.0f;

        glm::vec4 rectangleVertexData[4];
        glm::vec4 triangleVertexData[3];

        Renderer::Stats stats;

        Shr<Framebuffer> framebuffer;
    };

    static RenderData data;
    static int texSlots[data.MAX_TEXTURE_SLOTS];

    void Renderer::Init()
    {
        RenderCommand::Init();

        BufferLayout edgeGeometryLayout = {
            { GLSLDataType::FLOAT2, "aPos" },
            { GLSLDataType::FLOAT4, "aColor" },
            { GLSLDataType::FLOAT2, "aTexCoord" },
            { GLSLDataType::FLOAT , "aTilingFactor"},
            { GLSLDataType::INT , "aTexID" },
			{ GLSLDataType::INT , "aProjectionMode" },
            { GLSLDataType::INT , "aCoreID" }
        };

        BufferLayout LineGeometryLayout = {
            { GLSLDataType::FLOAT2, "aPos" },
            { GLSLDataType::FLOAT4, "aColor" },
			{ GLSLDataType::INT , "aProjectionMode" },
            { GLSLDataType::INT , "aCoreID" }
        };

        data.edgeGeometryShader = DataPool::GetShader("EdgeGeometryShader");
        data.edgeGeometryShader->Compile();

        data.lineGeometryShader = DataPool::GetShader("LineGeometryShader");
        data.lineGeometryShader->Compile();

        data.rectangleVertexArray = VertexArray::CreateArray();
        data.rectangleVertexBuffer = VertexBuffer::CreateBuffer(edgeGeometryLayout, data.MAX_VERTICES * sizeof(RectangleVertex));
        data.rectangleVertexArray->SetVertexBuffer(data.rectangleVertexBuffer);
        
        data.triangleVertexArray = VertexArray::CreateArray();
        data.triangleVertexBuffer = VertexBuffer::CreateBuffer(edgeGeometryLayout, data.MAX_VERTICES * sizeof(TriangleVertex));
        data.triangleVertexArray->SetVertexBuffer(data.triangleVertexBuffer);

        data.lineVertexArray = VertexArray::CreateArray();
        data.lineVertexBuffer = VertexBuffer::CreateBuffer(LineGeometryLayout, data.MAX_VERTICES * sizeof(LineVertex));
        data.lineVertexArray->SetVertexBuffer(data.lineVertexBuffer);

        data.rectangleVertexBufferBase = new RectangleVertex[data.MAX_VERTICES];
        
        data.triangleVertexBufferBase = new TriangleVertex[data.MAX_VERTICES];

        data.lineVertexBufferBase = new LineVertex[data.MAX_VERTICES];

        uint32_t* rectangleElements = new uint32_t[data.MAX_ELEMENTS];

        int offsetRectangle = 0;
        for (int i = 0; i < data.MAX_ELEMENTS; i += 6)
        {
            // first triangle
            rectangleElements[i + 0] = offsetRectangle + 0;
            rectangleElements[i + 1] = offsetRectangle + 1;
            rectangleElements[i + 2] = offsetRectangle + 2;
            // second triangle               
            rectangleElements[i + 3] = offsetRectangle + 2;
            rectangleElements[i + 4] = offsetRectangle + 3;
            rectangleElements[i + 5] = offsetRectangle + 0;

            offsetRectangle += 4;
        }

        Shr<ElementBuffer> rectangleElementbuffer = ElementBuffer::CreateBuffer(rectangleElements, data.MAX_ELEMENTS);
        data.rectangleVertexArray->SetElementBuffer(rectangleElementbuffer);
        delete[] rectangleElements;

        uint32_t* triangleElements = new uint32_t[data.MAX_ELEMENTS];
        
        int offsetTriangle = 0;
        for (int i = 0; i < data.MAX_ELEMENTS; i += 3)
        {
            triangleElements[i + 0] = offsetTriangle + 0;
            triangleElements[i + 1] = offsetTriangle + 1;
            triangleElements[i + 2] = offsetTriangle + 2;
        
            offsetTriangle += 3;
        }
        
        Shr<ElementBuffer> triangleElementbuffer = ElementBuffer::CreateBuffer(triangleElements, data.MAX_ELEMENTS);
        data.triangleVertexArray->SetElementBuffer(triangleElementbuffer);
        delete[] triangleElements;

        data.rectangleVertexData[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        data.rectangleVertexData[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        data.rectangleVertexData[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
        data.rectangleVertexData[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

        data.triangleVertexData[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        data.triangleVertexData[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        data.triangleVertexData[2] = glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f);

        for (uint32_t i = 0; i < data.MAX_TEXTURE_SLOTS; i++)
        {
            texSlots[i] = i;
        }

        FramebufferSpecification spec;
        spec.attachment = { FramebufferTexFormat::RGBA8, FramebufferTexFormat::RED_INTEGER, FramebufferTexFormat::Depth };
        spec.width = Application::GetWindow()->GetWidth();
        spec.height = Application::GetWindow()->GetHeight();
        data.framebuffer = Framebuffer::CreateBuffer(spec);
    }

    void Renderer::Shutdown()
    {
        delete[] data.rectangleVertexBufferBase;
        delete[] data.triangleVertexBufferBase;
        delete[] data.lineVertexBufferBase;
     }

    void Renderer::ResizeWindow(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }

    void Renderer::BeginRender(const Camera& camera)
    {
        data.camera = camera;
        data.camera.CalcCameraVectors();

        RenderCommand::Clear();
        data.framebuffer->Bind();
        RenderCommand::Clear();

        data.framebuffer->SetViewPort();
        data.framebuffer->ClearAttachment(1, 0); 

        StartBatch();
    }

    void Renderer::EndRender()
    {
        Render();
        data.framebuffer->Unbind();
    }

    void Renderer::StartBatch()
    {
        data.rectangleElementCount = 0;
        data.rectangleVertexBufferPtr = data.rectangleVertexBufferBase;
        data.rectangleTextureSlotIndex = 0;

        data.triangleElementCount = 0;
        data.triangleVertexBufferPtr = data.triangleVertexBufferBase;
        data.triangleTextureSlotIndex = 0;

        data.lineElementCount = 0;
        data.lineVertexBufferPtr = data.lineVertexBufferBase;
    }

    void Renderer::NextBatch()
    {
        Render();
        StartBatch();
    }


    void Renderer::Render()
    {
	    if (data.rectangleElementCount)
	    {
            const uint32_t dataSize = (uint32_t)((uint8_t*)data.rectangleVertexBufferPtr - (uint8_t*)data.rectangleVertexBufferBase);
            data.rectangleVertexBuffer->AddData(data.rectangleVertexBufferBase, dataSize);
            data.stats.dataSize += dataSize;

            //bind textures
            for (uint32_t i = 0; i < data.rectangleTextureSlotIndex; i++)
                data.rectangleTextureSlots[i]->Bind(i);

            data.edgeGeometryShader->Bind();
            data.edgeGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.edgeGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());
            data.edgeGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.edgeGeometryShader->UploadIntArray("uTexture", data.MAX_TEXTURE_SLOTS, texSlots);
            RenderCommand::DrawElements(data.rectangleVertexArray, data.rectangleElementCount);
            data.edgeGeometryShader->Unbind();
            data.stats.drawCalls++;

            //unbind textures
            for (uint32_t i = 0; i < data.rectangleTextureSlotIndex; i++)
                data.rectangleTextureSlots[i]->Unbind();
	    }

        if (data.triangleElementCount)
        {
            const uint32_t dataSize = (uint32_t)((uint8_t*)data.triangleVertexBufferPtr - (uint8_t*)data.triangleVertexBufferBase);
            data.triangleVertexBuffer->AddData(data.triangleVertexBufferBase, dataSize);
            data.stats.dataSize += dataSize;
        
            //bind textures
            for (uint32_t i = 0; i < data.triangleTextureSlotIndex; i++)
                data.triangleTextureSlots[i]->Bind(i);

            data.edgeGeometryShader->Bind();
            data.edgeGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.edgeGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.edgeGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());
            data.edgeGeometryShader->UploadIntArray("uTexture", data.MAX_TEXTURE_SLOTS, texSlots);
        	RenderCommand::DrawElements(data.triangleVertexArray, data.triangleElementCount);
            data.edgeGeometryShader->Unbind();
            data.stats.drawCalls++;
        
            //unbind textures
            for (uint32_t i = 0; i < data.triangleTextureSlotIndex; i++)
                data.triangleTextureSlots[i]->Unbind();
        }

        if (data.lineElementCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)data.lineVertexBufferPtr - (uint8_t*)data.lineVertexBufferBase);
            data.lineVertexBuffer->AddData(data.lineVertexBufferBase, dataSize);
            
            data.lineGeometryShader->Bind();
            data.lineGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.lineGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.lineGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());

            RenderCommand::SetLineThickness(data.lineWidth);
            RenderCommand::DrawLines(data.lineVertexArray, data.lineElementCount, data.lineWidth);
            data.lineGeometryShader->Unbind();
            data.stats.drawCalls++;
        }
    }

    void Renderer::DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawRectangle(transform, color, mode, coreID);
    }

    void Renderer::DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawRectangle(transform, texture, tilingFactor, color, mode, coreID);
    }

    void Renderer::DrawRectangle(glm::mat4 transform, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        const uint32_t rectangleVertexCount = 4;
        const int texIndex = -1;
        const glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const float tilingFactor = 1.0f;

        if (data.rectangleElementCount >= data.MAX_ELEMENTS)
        {
            NextBatch();
        }

        for (int i = 0; i < rectangleVertexCount; i++)
        {
            data.rectangleVertexBufferPtr->position = transform * data.rectangleVertexData[i];
            data.rectangleVertexBufferPtr->color = color;
            data.rectangleVertexBufferPtr->texCoords = texCoords[i];
            data.rectangleVertexBufferPtr->tilingFactor = tilingFactor;
            data.rectangleVertexBufferPtr->texIndex = texIndex;
            data.rectangleVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.rectangleVertexBufferPtr->coreID = coreID;
            data.rectangleVertexBufferPtr++;

            data.stats.vertexCount++;
        }

        data.rectangleElementCount += 6;

        data.stats.elementCount += 6;
        data.stats.objectCount++;
    }

    void Renderer::DrawRectangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        const uint32_t rectangleVertexCount = 4;
        constexpr glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        if (data.rectangleElementCount >= data.MAX_ELEMENTS)
        {
            NextBatch();
        }

        int texIndex = -1;
        for (uint32_t i = 0; i < data.rectangleTextureSlotIndex; i++)
        {
	        if (*data.rectangleTextureSlots[i] == *texture)
	        {
                texIndex = i;
                break;
	        }
        }

        if (texIndex == -1)
        {
            if (data.rectangleTextureSlotIndex >= data.MAX_TEXTURE_SLOTS)
                NextBatch();

            texIndex = data.rectangleTextureSlotIndex;
            data.rectangleTextureSlots[data.rectangleTextureSlotIndex] = texture;
            data.rectangleTextureSlotIndex++;
        }

        for (int i = 0; i < rectangleVertexCount; i++)
        {
            data.rectangleVertexBufferPtr->position = transform * data.rectangleVertexData[i];
            data.rectangleVertexBufferPtr->color = color;
            data.rectangleVertexBufferPtr->texCoords = texCoords[i];
            data.rectangleVertexBufferPtr->tilingFactor = tilingFactor;
            data.rectangleVertexBufferPtr->texIndex = texIndex;
            data.rectangleVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.rectangleVertexBufferPtr->coreID = coreID;
            data.rectangleVertexBufferPtr++;

            data.stats.vertexCount++;
        }

        data.rectangleElementCount += 6;

        data.stats.elementCount += 6;
        data.stats.objectCount++;
    }

    void Renderer::DrawTriangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
    
        DrawTriangle(transform, color, mode, coreID);
    }

    void Renderer::DrawTriangle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawTriangle(transform, texture, tilingFactor, color, mode, coreID);
    }

    void Renderer::DrawTriangle(glm::mat4 transform, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        const uint32_t triangleVertexCount = 3;
        const float texIndex = -1.0f;
        const glm::vec2 texCoords[3] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f } };
        const float tilingFactor = 1.0f;
        
        if (data.triangleElementCount >= data.MAX_ELEMENTS)
        {
            NextBatch();
        }
        
        for (int i = 0; i < triangleVertexCount; i++)
        {
            data.triangleVertexBufferPtr->position = transform * data.triangleVertexData[i];
            data.triangleVertexBufferPtr->color = color;
            data.triangleVertexBufferPtr->texCoords = texCoords[i];
            data.triangleVertexBufferPtr->tilingFactor = tilingFactor;
            data.triangleVertexBufferPtr->texIndex = texIndex;
            data.triangleVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.triangleVertexBufferPtr->coreID = coreID;
            data.triangleVertexBufferPtr++;
        
            data.stats.vertexCount++;
        }
        
        data.triangleElementCount += 3;
        
        data.stats.elementCount += 3;
        data.stats.objectCount++;
    }

    void Renderer::DrawTriangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID)
    {
        const uint32_t triangleVertexCount = 3;
        constexpr glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.5f, 1.0f } };

        if (data.triangleElementCount >= data.MAX_ELEMENTS)
        {
            NextBatch();
        }

        int texIndex = -1;
        for (uint32_t i = 0; i < data.triangleTextureSlotIndex; i++)
        {
            if (*data.triangleTextureSlots[i] == *texture)
            {
                texIndex = i;
                break;
            }
        }

        if (texIndex == -1)
        {
            if (data.triangleTextureSlotIndex >= data.MAX_TEXTURE_SLOTS)
                NextBatch();

            texIndex = data.triangleTextureSlotIndex;
            data.triangleTextureSlots[data.triangleTextureSlotIndex] = texture;
            data.triangleTextureSlotIndex++;
        }

        for (int i = 0; i < triangleVertexCount; i++)
        {
            data.triangleVertexBufferPtr->position = transform * data.triangleVertexData[i];
            data.triangleVertexBufferPtr->color = color;
            data.triangleVertexBufferPtr->texCoords = texCoords[i];
            data.triangleVertexBufferPtr->tilingFactor = tilingFactor;
            data.triangleVertexBufferPtr->texIndex = texIndex;
            data.triangleVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.triangleVertexBufferPtr->coreID = coreID;
            data.triangleVertexBufferPtr++;

            data.stats.vertexCount++;
        }

        data.triangleElementCount += 3;

        data.stats.elementCount += 3;
        data.stats.objectCount++;
    }

    void Renderer::DrawLine(glm::vec2 p0, glm::vec2 p1, glm::vec4 color, float thickness, ProjectionMode mode, core_id coreID)
    {
        const uint32_t lineVertexCount = 2;

        data.lineVertexBufferPtr->position = p0;
        data.lineVertexBufferPtr->color = color;
        data.lineVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
        data.lineVertexBufferPtr->coreID = coreID;
        data.lineVertexBufferPtr++;

        data.stats.vertexCount++;
        
        data.lineVertexBufferPtr->position = p1;
        data.lineVertexBufferPtr->color = color;
        data.lineVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
        data.lineVertexBufferPtr->coreID = coreID;
        data.lineVertexBufferPtr++;

        data.stats.vertexCount++;

        data.lineElementCount += 2;

        data.stats.elementCount += 1;
        data.stats.objectCount++;

        data.lineWidth = thickness;
        NextBatch();
    }


    Renderer::Stats Renderer::GetStats()
    {
        return data.stats;
    }

    void Renderer::ClearStats()
    {
        memset(&data.stats, 0, sizeof(Stats));
    }

    Shr<Framebuffer> Renderer::GetFramebuffer()
    {
        return data.framebuffer;
    }
}
