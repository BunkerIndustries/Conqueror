#pragma once
#include "utility.h"

#include "renderer/RenderBatch.h"
#include "renderer/FrameBuffer.h"
#include "generic/GameObject.h"
#include "component/SpriteRenderer.h"
#include "layer/LayerStack.h"

namespace core {
    
    class CORE_API Renderer {
    private:
        static Renderer* instance;

        const int MAX_BATCH_SIZE = 1000;
        std::vector<RenderBatch*> batches;
        std::vector<GameObject*> game_objects_in_use;
        FramebufferSpecification properties;
        FrameBuffer* frame_buffer = nullptr;

        int mouseHoverID[2] = { -1, -1 };
        int mouseClickedID[2] = { -1, -1 };
        bool pressed = false;

        inline static int sprites_count = 0;
        inline static int vertex_count = 0;

        glm::vec2 viewportSize;
    public:
        Renderer();
        ~Renderer();
        void add(Layer* layer, int index);
        void add(SpriteRenderer* spriteRenderer, int index);
        // this function has to be called on every frame (update)
        void render(float dt);
        void updateGameObjects(float dt);

        FrameBuffer& GetFrameBuffer() const { return *frame_buffer; }

        inline static int GetVerticesCount() { return vertex_count; }
        inline static int GetSpriteCount() { return sprites_count; }
        inline static int GetBatchCount() { return instance->batches.size(); }
    };

}