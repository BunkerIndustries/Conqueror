#pragma once
#include "_Core.h"
#include "utility.h"

#include "Object.h"
#include "generic/Transform.h"
#include "utils/DataPool.h"
#include "event/Event.h"

namespace core {

    class Component;
    class Layer;

    class GameObject : public Object {
    public:
        GameObject(std::string name, const Transform& transform = Transform(), ProjectionMode mode = ProjectionMode::PERSPECTIVE);

        ~GameObject() override;

        template<typename T>
        T* GetComponent();

        template<typename T>
        bool RemoveComponent();

        bool AddComponent(Component* component);

        void Update();
        void Start();
        void Stop();
        void Imgui(float dt);
        void OnEvent(Event& event);

        void DeleteComponents();

        GameObject* AddTag(std::string tag);
        GameObject* AddTag(std::initializer_list<std::string> tags);
        bool RemoveTag(std::string tag);
        bool HasTag(std::string tag);

        Layer* GetLayer() const { return this->layer; }
        bool IsRunning() const { return running; }

        ProjectionMode GetProjectionMode() const
        {
            return mode;
        }

        bool onlyLayerReceive = true;
        

    private:
        std::vector<Component*> components;
        Layer* layer = nullptr;
        bool deleted = false;

        std::initializer_list<std::string> tags;
        ProjectionMode mode;

        bool running = false;


        std::vector<std::string> tagList;

        void StopComponentIndex(uint32_t index);
        void DeleteComponentIndex(uint32_t index);

        friend class Layer;
        void SetLayer(Layer* layer);

    };

    template <typename T>
    T* GameObject::GetComponent()
    {
        T* derived = nullptr;
        for (Component* com : components)
        {
            derived = dynamic_cast<T*>(com);
            if (derived != nullptr) break;
        }
        return derived;
    }

    template <typename T>
    bool GameObject::RemoveComponent() {
        for (int i = 0; i < components.size(); i++)
        {
            if (dynamic_cast<T*>(components[i]) != nullptr) {
                if (running)
                    StopComponentIndex(i);
                DeleteComponentIndex(i);
                components.erase(components.begin() + i);
                return true;
            }
        }
        return false;
    }
}
