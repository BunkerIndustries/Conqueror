#pragma once
#include "_Core.h"

#include "generic/Shader.h"
#include "renderer/Texture.h"
#include "component/SpriteRenderer.h"
#include "utils/DataPool.h"

namespace core {

    class RenderBatch {
    private:
        const int POS_SIZE = 2;
        const int COLOR_SIZE = 4;
        const int TEX_COORDS_SIZE = 2;
        const int TEX_ID_SIZE = 1;
        const int CORE_ID_SIZE = 1;

        const int POS_OFFSET = 0;
        const int COLOR_OFFSET = sizeof(float) * (POS_SIZE);
        const int TEX_COORDS_OFFSET = sizeof(float) * (POS_SIZE + COLOR_SIZE);
        const int TEX_ID_OFFSET = sizeof(float) * (POS_SIZE + COLOR_SIZE + TEX_COORDS_SIZE);
        const int CORE_ID_OFFSET = sizeof(float) * (POS_SIZE + COLOR_SIZE + TEX_COORDS_SIZE + TEX_ID_SIZE);

        const int VERTEX_SIZE = POS_SIZE + COLOR_SIZE + TEX_COORDS_SIZE + TEX_ID_SIZE + CORE_ID_SIZE;
        const int VERTEX_SIZE_BYTES = sizeof(float) * VERTEX_SIZE;

        bool hasRoom_bool = false;


        //std::vector<float> vertices;
        std::vector<int> texSlots = { 0, 1, 2, 3 , 4, 5, 6, 7 };
        std::vector<std::shared_ptr<Texture>> textures;
        std::vector<SpriteRenderer*> sprites;

        unsigned int vaoID;
        unsigned int vboID;
        unsigned int eboID;

        int numSprites;
        int maxBatchSize;
        int zIndex;

        std::shared_ptr<Shader> shader;
        std::vector<float> vertices;
        unsigned int* elements;

        void updateTextures();
        void loadVertexProperties(int index);
        void generateIndices(unsigned int* element);
        void loadElementIndices(unsigned int* arrayElements, int index);



        inline static int draw_calls = 0;
        inline static bool enable_polygon = false;
        inline static int polygonMode = 6914;

    public:

        RenderBatch(int maxBatchSize, int zIndex, DataPool::DISPLAYMODE displaymode);
        ~RenderBatch();
        void start();
        void addSprite(SpriteRenderer* sprite_renderer);
        bool hasSprite(SpriteRenderer* sprite_renderer);
        void render();

        bool hasRoom();
        bool hasTextureRoom();
        bool hasTexture(std::shared_ptr<Texture> texture);

        int getZIndex();

        DataPool::DISPLAYMODE displayMode;

        int GetSpritesCount() const;
        int GetVertexCount() const; 

        inline static void setPolygonMode(int mode)
        {
            polygonMode = mode;
        }

        static int GetDrawCalls() { return draw_calls; }
    };

}