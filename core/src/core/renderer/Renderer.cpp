#include "_Core.h"

#include "renderer/Renderer.h"
#include "renderer/RenderCommand.h"
#include "utils/DataPool.h"
#include "renderer/Shader.h"
#include "generic/Application.h"
#include "imgui/ImGuiLayer.h"

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
        int uiID;
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
        int uiID;
    };

    struct LineVertex
    {
        glm::vec2 position;
        glm::vec4 color;
        int projectionMode;
        int coreID;
        int uiID;
    };

    struct CircleVertex
    {
        glm::vec2 worldPos;
        glm::vec2 localPos;

        glm::vec2 texCoords;
        float tilingFactor;
        int texIndex;

        glm::vec4 color;
        float thickness;
        float fade;

        int projectionMode;
        int coreID;
    };

    struct TextVertex
    {
        glm::vec2 position;
        glm::vec4 color;
        glm::vec2 texCoord;

        int projectionMode;
        int coreID;
        int uiID;
    };

    struct RenderData
    {
        static constexpr uint32_t MAX_VERTICES = 40000;
        static constexpr uint32_t MAX_ELEMENTS = 60000;
        static constexpr uint32_t MAX_TEXTURE_SLOTS = 32;

        Shr<Shader> edgeGeometryShader;
        Shr<Shader> lineGeometryShader;
        Shr<Shader> circleGeometryShader;
        Shr<Shader> textShader;

        Shr<VertexArray> rectangleVertexArray;
        Shr<VertexBuffer> rectangleVertexBuffer;

        Shr<VertexArray> lineVertexArray;
        Shr<VertexBuffer> lineVertexBuffer;

        Shr<VertexArray> triangleVertexArray;
        Shr<VertexBuffer> triangleVertexBuffer;

        Shr<VertexArray> circleVertexArray;
        Shr<VertexBuffer> circleVertexBuffer;

        Shr<VertexArray> textVertexArray;
        Shr<VertexBuffer> textVertexBuffer;
        
        uint32_t rectangleElementCount = 0;
        RectangleVertex* rectangleVertexBufferBase = nullptr;
        RectangleVertex* rectangleVertexBufferPtr = nullptr;

        uint32_t triangleElementCount = 0;
        TriangleVertex* triangleVertexBufferBase = nullptr;
        TriangleVertex* triangleVertexBufferPtr = nullptr;

        uint32_t lineElementCount = 0;
        LineVertex* lineVertexBufferBase = nullptr;
        LineVertex* lineVertexBufferPtr = nullptr;

        uint32_t circleElementCount = 0;
        CircleVertex* circleVertexBufferBase = nullptr;
        CircleVertex* circleVertexBufferPtr = nullptr;

        uint32_t textElementCount = 0;
        TextVertex* textVertexBufferBase = nullptr;
        TextVertex* textVertexBufferPtr = nullptr;

        std::array<Shr<Texture>, MAX_TEXTURE_SLOTS> rectangleTextureSlots;
        uint32_t rectangleTextureSlotIndex = 0;

        std::array<Shr<Texture>, MAX_TEXTURE_SLOTS> triangleTextureSlots;
        uint32_t triangleTextureSlotIndex = 0;

        std::array<Shr<Texture>, MAX_TEXTURE_SLOTS> circleTextureSlots;
        uint32_t circleTextureSlotIndex = 0;

        Camera camera;

        float lineWidth = 1.0f;

        glm::vec4 rectangleVertexData[4];
        glm::vec4 triangleVertexData[3];

        Renderer::Stats stats;

        Shr<Framebuffer> framebuffer;


        Shr<Texture> fontAtlasTexture;

    };

    static RenderData data;
    static int texSlots[data.MAX_TEXTURE_SLOTS - 1];

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
            { GLSLDataType::INT , "aCoreID" },
            { GLSLDataType::INT , "aUIID" }
        };

        BufferLayout lineGeometryLayout = {
            { GLSLDataType::FLOAT2, "aPos" },
            { GLSLDataType::FLOAT4, "aColor" },
			{ GLSLDataType::INT , "aProjectionMode" },
            { GLSLDataType::INT , "aCoreID" },
            { GLSLDataType::INT , "aUIID" }
        };

        BufferLayout circleGeometryLayout = {
            { GLSLDataType::FLOAT2, "aWorldPos" },
            { GLSLDataType::FLOAT2, "aLocalPos" },

			{ GLSLDataType::FLOAT2, "aTexCoord" },
			{ GLSLDataType::FLOAT , "aTilingFactor"},
            { GLSLDataType::INT , "aTexID" },

            { GLSLDataType::FLOAT4, "aColor" },
            { GLSLDataType::FLOAT,  "aThickness" },
            { GLSLDataType::FLOAT,  "aFade" },

			{ GLSLDataType::INT , "aProjectionMode" },
            { GLSLDataType::INT, "aCoreID" }
        };

        BufferLayout textLayout
        {
            { GLSLDataType::FLOAT2, "aPos" },
            { GLSLDataType::FLOAT4, "aColor" },
            { GLSLDataType::FLOAT2, "aTexCoord" },

            { GLSLDataType::INT ,   "aProjectionMode" },
            { GLSLDataType::INT,    "aCoreID" },
            { GLSLDataType::INT , "aUIID" }
        };

        data.edgeGeometryShader = DataPool::GetShader("EdgeGeometryShader");
        data.edgeGeometryShader->Compile();

        data.lineGeometryShader = DataPool::GetShader("LineGeometryShader");
        data.lineGeometryShader->Compile();

        data.circleGeometryShader = DataPool::GetShader("CircleGeometryShader");
        data.circleGeometryShader->Compile();

        data.textShader = DataPool::GetShader("TextShader");
        data.textShader->Compile();

        data.rectangleVertexArray = VertexArray::CreateArray();
        data.rectangleVertexBuffer = VertexBuffer::CreateBuffer(edgeGeometryLayout, data.MAX_VERTICES * sizeof(RectangleVertex));
        data.rectangleVertexArray->SetVertexBuffer(data.rectangleVertexBuffer);
        
        data.triangleVertexArray = VertexArray::CreateArray();
        data.triangleVertexBuffer = VertexBuffer::CreateBuffer(edgeGeometryLayout, data.MAX_VERTICES * sizeof(TriangleVertex));
        data.triangleVertexArray->SetVertexBuffer(data.triangleVertexBuffer);

        data.circleVertexArray = VertexArray::CreateArray();
        data.circleVertexBuffer = VertexBuffer::CreateBuffer(circleGeometryLayout, data.MAX_VERTICES * sizeof(CircleVertex));
        data.circleVertexArray->SetVertexBuffer(data.circleVertexBuffer);

        data.lineVertexArray = VertexArray::CreateArray();
        data.lineVertexBuffer = VertexBuffer::CreateBuffer(lineGeometryLayout, data.MAX_VERTICES * sizeof(LineVertex));
        data.lineVertexArray->SetVertexBuffer(data.lineVertexBuffer);

        data.textVertexArray = VertexArray::CreateArray();
        data.textVertexBuffer = VertexBuffer::CreateBuffer(textLayout, data.MAX_VERTICES * sizeof(TextVertex));
        data.textVertexArray->SetVertexBuffer(data.textVertexBuffer);

        

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

        data.textVertexArray->SetElementBuffer(rectangleElementbuffer);
        data.circleVertexArray->SetElementBuffer(rectangleElementbuffer);

        data.rectangleVertexData[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        data.rectangleVertexData[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        data.rectangleVertexData[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
        data.rectangleVertexData[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

        data.triangleVertexData[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        data.triangleVertexData[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        data.triangleVertexData[2] = glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f);

        data.rectangleVertexBufferBase = new RectangleVertex[data.MAX_VERTICES];
        data.triangleVertexBufferBase = new TriangleVertex[data.MAX_VERTICES];
        data.circleVertexBufferBase = new CircleVertex[data.MAX_VERTICES];
        data.lineVertexBufferBase = new LineVertex[data.MAX_VERTICES];
        data.textVertexBufferBase = new TextVertex[data.MAX_VERTICES];

        for (uint32_t i = 0; i < data.MAX_TEXTURE_SLOTS - 1; i++)
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
        delete[] data.textVertexBufferBase;
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

        data.circleElementCount = 0;
        data.circleVertexBufferPtr = data.circleVertexBufferBase;
        data.circleTextureSlotIndex = 0;

        data.textElementCount = 0;
        data.textVertexBufferPtr = data.textVertexBufferBase;
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

            //data.framebuffer->BindAttachmentAsTexture(1, data.MAX_TEXTURE_SLOTS - 1);

            data.edgeGeometryShader->Bind();
            data.edgeGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.edgeGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());
            data.edgeGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.edgeGeometryShader->UploadIntArray("uTexture", data.MAX_TEXTURE_SLOTS - 1, texSlots);
            //data.edgeGeometryShader->UploadInt("uIDAttachment", data.MAX_TEXTURE_SLOTS - 1);
            //data.edgeGeometryShader->UploadVec2f("screenSize", glm::vec2(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight()));
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

            //data.framebuffer->BindAttachmentAsTexture(1, data.MAX_TEXTURE_SLOTS - 1);

            data.edgeGeometryShader->Bind();
            data.edgeGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.edgeGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.edgeGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());
            data.edgeGeometryShader->UploadIntArray("uTexture", data.MAX_TEXTURE_SLOTS, texSlots);
            //data.edgeGeometryShader->UploadInt("uIDAttachment", data.MAX_TEXTURE_SLOTS - 1);
            //data.edgeGeometryShader->UploadVec2f("screenSize", glm::vec2(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight()));
        	RenderCommand::DrawElements(data.triangleVertexArray, data.triangleElementCount);
            data.edgeGeometryShader->Unbind();
            data.stats.drawCalls++;
        
            //unbind textures
            for (uint32_t i = 0; i < data.triangleTextureSlotIndex; i++)
                data.triangleTextureSlots[i]->Unbind();
        }

        if (data.circleElementCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)data.circleVertexBufferPtr - (uint8_t*)data.circleVertexBufferBase);
            data.circleVertexBuffer->AddData(data.circleVertexBufferBase, dataSize);
            data.stats.dataSize += dataSize;


            //bind textures
            for (uint32_t i = 0; i < data.circleTextureSlotIndex; i++)
                data.circleTextureSlots[i]->Bind(i);

            data.circleGeometryShader->Bind();
            data.circleGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.circleGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.circleGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());
            data.circleGeometryShader->UploadIntArray("uTexture", data.MAX_TEXTURE_SLOTS, texSlots);
            RenderCommand::DrawIndexed(data.circleVertexArray, data.circleElementCount);
            data.circleGeometryShader->Unbind();
            data.stats.drawCalls++;

            for (uint32_t i = 0; i < data.circleTextureSlotIndex; i++)
                data.circleTextureSlots[i]->Unbind();
        }

        if (data.lineElementCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)data.lineVertexBufferPtr - (uint8_t*)data.lineVertexBufferBase);
            data.lineVertexBuffer->AddData(data.lineVertexBufferBase, dataSize);
            data.stats.dataSize += dataSize;

            
            data.lineGeometryShader->Bind();
            data.lineGeometryShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.lineGeometryShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.lineGeometryShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());

            RenderCommand::SetLineThickness(data.lineWidth);
            RenderCommand::DrawLines(data.lineVertexArray, data.lineElementCount, data.lineWidth);
            data.lineGeometryShader->Unbind();
            data.stats.drawCalls++;
        }

        if (data.textElementCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)data.textVertexBufferPtr - (uint8_t*)data.textVertexBufferBase);
            data.textVertexBuffer->AddData(data.textVertexBufferBase, dataSize);
            data.stats.dataSize += dataSize;


            data.fontAtlasTexture->Bind(0);

            data.textShader->Bind();

        	data.textShader->UploadMat4f("uPerspective", data.camera.GetProjectionMatrix());
            data.textShader->UploadMat4f("uView", data.camera.GetViewMatrix());
            data.textShader->UploadMat4f("uOrthographic", data.camera.GetOrthographicMatrix());

            RenderCommand::DrawIndexed(data.textVertexArray, data.textElementCount);
            data.stats.drawCalls++;
        }
    }

    void Renderer::DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawRectangle(transform, color, mode, coreID, uiID);
    }

    void Renderer::DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawRectangle(transform, texture, tilingFactor, color, mode, coreID, uiID);
    }

    // sprite sheet entry function
    void Renderer::DrawRectangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec2 texCoordSprite[4], Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawRectangle(transform, texture, tilingFactor, texCoordSprite, color, mode, coreID, uiID);
    }

    void Renderer::DrawRectangle(glm::mat4 transform, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
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

    void Renderer::DrawRectangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
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
    

    

    // mandatory for sprite sheets

    void Renderer::DrawRectangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec2 texCoordSprite[4], glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        const uint32_t rectangleVertexCount = 4;

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
            data.rectangleVertexBufferPtr->texCoords = texCoordSprite[i];
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

    void Renderer::DrawTriangle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
    
        DrawTriangle(transform, color, mode, coreID, uiID);
    }


    

    void Renderer::DrawTriangle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawTriangle(transform, texture, tilingFactor, color, mode, coreID, uiID);
    }

    void Renderer::DrawTriangle(glm::mat4 transform, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
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

    void Renderer::DrawTriangle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, ProjectionMode mode, core_id coreID, core_id uiID)
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


    void Renderer::DrawLine(glm::vec2 p0, glm::vec2 p1, glm::vec4 color, float thickness, ProjectionMode mode, core_id coreID, core_id uiID)
    {
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

    void Renderer::DrawCircle(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, float thickness, float fade, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawCircle(transform, color, thickness, fade, mode, coreID, uiID);
    }

    void Renderer::DrawCircle(glm::vec2 position, glm::vec2 size, float rotation, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, float thickness, float fade, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        DrawCircle(transform, texture, tilingFactor, color, thickness, fade, mode, coreID, uiID);
    }

    void Renderer::DrawCircle(glm::mat4 transform, glm::vec4 color, float thickness, float fade, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        const uint32_t circleVertexCount = 4;
        const float texIndex = -1.0f;
        const glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const float tilingFactor = 1.0f;

        if (data.circleElementCount >= data.MAX_ELEMENTS)
        {
            NextBatch();
        }

        for (int i = 0; i < circleVertexCount; i++)
        {
            data.circleVertexBufferPtr->worldPos = transform * data.rectangleVertexData[i];
            data.circleVertexBufferPtr->localPos = data.rectangleVertexData[i] * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f)); // just multiplying x and y by 2
            data.circleVertexBufferPtr->texCoords = texCoords[i];
            data.circleVertexBufferPtr->tilingFactor = tilingFactor;
            data.circleVertexBufferPtr->texIndex = texIndex;
        	data.circleVertexBufferPtr->color = color;
            data.circleVertexBufferPtr->thickness = thickness;
            data.circleVertexBufferPtr->fade = fade;
            data.circleVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.circleVertexBufferPtr->coreID = coreID;
            data.circleVertexBufferPtr++;
            data.stats.vertexCount++;
        }

        data.circleElementCount += 6;

        data.stats.elementCount += 6;
        data.stats.objectCount++;
    }

    void Renderer::DrawCircle(glm::mat4 transform, Shr<Texture>& texture, float tilingFactor, glm::vec4 color, float thickness, float fade, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        const uint32_t circleVertexCount = 4;
        constexpr glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        if (data.circleElementCount >= data.MAX_ELEMENTS)
        {
            NextBatch();
        }

        int texIndex = -1;
        for (uint32_t i = 0; i < data.circleTextureSlotIndex; i++)
        {
            if (*data.circleTextureSlots[i] == *texture)
            {
                texIndex = i;
                break;
            }
        }

        if (texIndex == -1)
        {
            if (data.circleTextureSlotIndex >= data.MAX_TEXTURE_SLOTS)
                NextBatch();

            texIndex = data.circleTextureSlotIndex;
            data.circleTextureSlots[data.circleTextureSlotIndex] = texture;
            data.circleTextureSlotIndex++;
        }

        for (int i = 0; i < circleVertexCount; i++)
        {
            data.circleVertexBufferPtr->worldPos = transform * data.rectangleVertexData[i];
            data.circleVertexBufferPtr->localPos = data.rectangleVertexData[i] * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f)); // just multiplying x and y by 2
            data.circleVertexBufferPtr->texCoords = texCoords[i];
            data.circleVertexBufferPtr->tilingFactor = tilingFactor;
            data.circleVertexBufferPtr->texIndex = texIndex;
            data.circleVertexBufferPtr->color = color;
            data.circleVertexBufferPtr->thickness = thickness;
            data.circleVertexBufferPtr->fade = fade;
            data.circleVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.circleVertexBufferPtr->coreID = coreID;
            data.circleVertexBufferPtr++;
            data.stats.vertexCount++;
        }

        data.circleElementCount += 6;

        data.stats.elementCount += 6;
        data.stats.objectCount++;
    }
    static float con = 2.5f;
    void Renderer::DrawString(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, std::string string, Shr<Font> font, ProjectionMode mode, core_id coreID, core_id uiID)
    {
        

        const auto& fontGeometry = font->GetMSDFData()->FontGeometry;
        const auto& metrics = fontGeometry.getMetrics();
        Shr<Texture> fontAtlas = font->GetAtlasTexture();

        data.fontAtlasTexture = fontAtlas;

        double x = 0.0;
        double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
        double y = 0.0;
        float lineHeightOffset = 0.0f;

        position.y -= fsScale / 2.5;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        for (size_t i = 0; i < string.size(); i++)
        {
            char character = string[i];
            if (character == '\r')
                continue;

            if (character == '\n')
            {
                x = 0;
                y -= fsScale * metrics.lineHeight + lineHeightOffset;
                continue;
            }
            auto glyph = fontGeometry.getGlyph(character);
            if (!glyph)
                glyph = fontGeometry.getGlyph('?');
            if (!glyph)
                return;

            if (character == '\t')
                glyph = fontGeometry.getGlyph('   ');

            double al, ab, ar, at;
            glyph->getQuadAtlasBounds(al, ab, ar, at);
            glm::vec2 texCoordMin((float)al, (float)ab);
            glm::vec2 texCoordMax((float)ar, (float)at);

            double pl, pb, pr, pt;
            glyph->getQuadPlaneBounds(pl, pb, pr, pt);
            glm::vec2 quadMin((float)pl, (float)pb);
            glm::vec2 quadMax((float)pr, (float)pt);

            quadMin *= fsScale, quadMax *= fsScale;
            quadMin += glm::vec2(x, y);
            quadMax += glm::vec2(x, y);

            float texelWidth = 1.0f / fontAtlas->GetWidth();
            float texelHeight = 1.0f / fontAtlas->GetHeight();
            texCoordMin *= glm::vec2(texelWidth, texelHeight);
            texCoordMax *= glm::vec2(texelWidth, texelHeight);

            // render here
            data.textVertexBufferPtr->position = transform * glm::vec4(quadMin, 0.0f, 1.0f);
            data.textVertexBufferPtr->color = color;
            data.textVertexBufferPtr->texCoord = texCoordMin;
            data.textVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.textVertexBufferPtr->coreID = coreID; // TODO
            data.textVertexBufferPtr++;
            data.stats.vertexCount++;

            data.textVertexBufferPtr->position = transform * glm::vec4(quadMin.x, quadMax.y, 0.0f, 1.0f);
            data.textVertexBufferPtr->color = color;
            data.textVertexBufferPtr->texCoord = { texCoordMin.x, texCoordMax.y };
            data.textVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.textVertexBufferPtr->coreID = coreID; // TODO
            data.textVertexBufferPtr++;
            data.stats.vertexCount++;

            data.textVertexBufferPtr->position = transform * glm::vec4(quadMax, 0.0f, 1.0f);
            data.textVertexBufferPtr->color = color;
            data.textVertexBufferPtr->texCoord = texCoordMax;
            data.textVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.textVertexBufferPtr->coreID = coreID; // TODO
            data.textVertexBufferPtr++;
            data.stats.vertexCount++;

            data.textVertexBufferPtr->position = transform * glm::vec4(quadMax.x, quadMin.y, 0.0f, 1.0f);
            data.textVertexBufferPtr->color = color;
            data.textVertexBufferPtr->texCoord = { texCoordMax.x, texCoordMin.y };
            data.textVertexBufferPtr->projectionMode = ProjectionModeToInt(mode);
            data.textVertexBufferPtr->coreID = coreID; // TODO
            data.textVertexBufferPtr++;
            data.stats.vertexCount++;

            data.textElementCount += 6;

            data.stats.elementCount += 6;
            data.stats.objectCount++;

            if (i < string.size() - 1)
            {
                double advance = glyph->getAdvance();
                char nextCharacter = string[i + 1];
                fontGeometry.getAdvance(advance, character, nextCharacter);

                float kerningOffset = 0.0f;
                x += fsScale * advance + kerningOffset;
            }
        }
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
