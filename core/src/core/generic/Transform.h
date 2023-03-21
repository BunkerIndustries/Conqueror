#pragma once
#include "_Core.h"
#include "utility.h"


namespace core {

    class Transform {
    public:
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;

        Transform();
        ~Transform();
        Transform(glm::vec2 position);
        Transform(glm::vec2 position, glm::vec2 scale);
        Transform(glm::vec2 position, glm::vec2 scale, float rotation);

        void Init(glm::vec2 position, glm::vec2 scale, float rotation);


        Transform* Copy();
        // copy new values to transform
        void Copy(Transform& transform);
        bool Equals(Transform& transform);

    private:
        void Update();

        friend class GameObject;
    };

}