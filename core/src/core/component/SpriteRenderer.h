#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Component.h"
#include "generic/Transform.h"
#include "component/Sprite.h"

namespace core {

    class CORE_API SpriteRenderer : public Component {
    private:
        glm::vec4 color;
        Sprite* sprite;
        Transform* lastTransform;

        bool isDirty = false;
    public:
        SpriteRenderer(glm::vec4 color);
        SpriteRenderer(Sprite* sprite);

        virtual ~SpriteRenderer();

        void start() override;
        void stop() override { }
        void update(float dt) override;
        void imgui(float dt) override;
        void event(Event& event) override { }

        glm::vec4 getColor();
        std::shared_ptr<Texture> getTexture();
    	float* getTexCoords();

        void setSprite(Sprite* sprite);
        void setColor(glm::vec4 color);

        bool getIsDirty();
        void setClean();

    };

}