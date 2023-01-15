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
        const int MAX_BATCH_SIZE = 1000;
        std::vector<RenderBatch*> batches;
        std::vector<GameObject*> game_objects_in_use;
        FrameBufferProperties properties;
        FrameBuffer* frame_buffer = nullptr;
    public:
        Renderer();
        ~Renderer();
        void add(Layer* layer, int index);
        void add(SpriteRenderer* spriteRenderer, int index);
        // this function has to be called on every frame (update)
        void render(LayerStack& layer_stack, float dt);
        void updateGameObjects(float dt, std::vector<GameObject*>& gameObjects);

        FrameBuffer& GetFrameBuffer() const { return *frame_buffer; }
    };

}