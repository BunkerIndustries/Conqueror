#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Component.h"
#include "renderer/Texture.h"

namespace core {

    class Sprite : public Component {
    private:
        std::shared_ptr<Texture> texture;
        float texCoords[8];
    public:
        Sprite(std::shared_ptr<Texture> texture);
        Sprite(std::shared_ptr<Texture> texture, float* texCoords);
        virtual ~Sprite();

        void start() override { }
        void stop() override { }
        void update(float dt) override { }
        void event(Event& event) override { }

        void setTexture(std::shared_ptr<Texture> texture);
        std::shared_ptr<Texture> getTexture();

        float* getTexCoords();
    };

}