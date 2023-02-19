#pragma once
#include "utility.h"

#include "renderer/RenderBatch.h"
#include "renderer/FrameBuffer.h"
#include "generic/GameObject.h"

#include "renderer/RenderCommand.h"
#include "generic/Camera.h"

namespace core {

    struct RenderData
    {
        int zIndex;
        ProjectionMode projectionMode;

    protected:
        RenderData() = default;
    };

    struct TriangleData : RenderData
    {
        std::vector<float> vertices;
        std::vector<unsigned int> elements;
        //std::vector<Shr<Texture>> textures;

        TriangleData()
        {
            vertices.resize(0);
            elements.resize(0);
            //textures.resize(0);
            zIndex = 0;
            projectionMode = ProjectionMode::PERSPECTIVE;
        }

    private:
        int id = 0;

        std::vector<Shr<Texture>> oldTextures;
    };

    class Renderer {
    public:
        enum RenderType
        {
	        NONE = 0,
            TRIANGLE,
            CIRCLE,
            LINE
        };

        static void Init();
        static void Shutdown();


        static void SubmitData(RenderData* renderData);
        static void Render(Shr<Camera>& camera);


    private:
        static std::vector<std::vector<RenderData*>> batches;

        static Shr<VertexArray> triangleVertexArray;
        static Shr<VertexBuffer> triangleVertexBuffer;
        static Shr<ElementBuffer> triangleElementBuffer;

        static constexpr uint32_t MAX_VERTICES = 40000;
        static constexpr uint32_t MAX_ELEMENTS = 60000;
        static constexpr uint32_t MAX_TEXTURE_SLOTS = 32;

/*
    private:
        static Renderer* instance;

        const int MAX_BATCH_SIZE = 1000;
        std::vector<RenderBatch*> batches;
        std::vector<GameObject*> game_objects_in_use;
        FramebufferSpecification properties;
        Shr<Framebuffer> framebuffer = nullptr;

        int mouseHoverID[2] = { -1, -1 };
        int mouseClickedID[2] = { -1, -1 };
        bool pressed = false;

        inline static int sprites_count = 0;
        inline static int vertex_count = 0;

        glm::vec2 viewportSize;
    public:
        Renderer();
        ~Renderer();
        void add(RenderData* renderData);
        void remove(RenderData* renderData);
        // this function has to be called on every frame (update)
        void render(float dt);
        void updateGameObjects(float dt);

        Shr<Framebuffer> GetFrameBuffer() const { return framebuffer; }
        */
    };

}