#pragma once
#include "_Core.h"
#include "generic/Component.h"

namespace core
{
    class CircleRenderer : public Component {
    public:

        CircleRenderer(glm::vec2 position, glm::vec2 size, glm::vec4 color, float rotation, float thickness, float fade);

        ~CircleRenderer() override { }

        void OnStart() override { }
        void OnStop() override { }
        void OnUpdate() override;
        void OnImgui(float dt) override;
        void OnEvent(Event& event) override { }

        void SetColor(glm::vec4 color) { this->color = color; }

    private:
        glm::vec4 color;
        glm::mat4 transform;
        float rotation;
        float thickness;
        float fade;
    };
}


