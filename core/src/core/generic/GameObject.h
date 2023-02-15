#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Transform.h"
#include "utils/DataPool.h"
#include "event/Event.h"

namespace core {

    class Component;
    class SpriteRenderer;

    struct GOSpec {
        std::string name = "GameObject";
        std::initializer_list<std::string> tags;
        Transform transform = Transform();
        ProjectionMode mode = ProjectionMode::PERSPECTIVE;
    };

    class GameObject {
    private:
        std::string name;
        std::vector<Component*> components;
        int zIndex;

        bool running = false;

        core_id objectID;

        std::vector<std::string> tagList;

        void StopComponentIndex(uint32_t index);
        void DeleteComponentIndex(uint32_t index);

        static std::unordered_map<core_id, GameObject*> IDMap;
    public:
        Transform transform;
        GameObject(std::string name, Transform& transform = Transform(), ProjectionMode mode = ProjectionMode::PERSPECTIVE);


        ~GameObject();

        template<typename T>
        T* GetComponent();

        template<typename T>
        bool RemoveComponent();

        bool AddComponent(Component* component);

        void update(float dt);
        void start();
        void stop();
        void imgui(float dt);
        void event(Event& event);

        void deleteComponents();

        GameObject* AddTag(std::string tag);
        GameObject* AddTag(std::initializer_list<std::string> tags);
        bool RemoveTag(std::string tag);
        bool HasTag(std::string tag);

        std::string GetName() { return this->name; }
        int GetZIndex() { return this->zIndex; }
        void SetZIndex(int zIndex) { this->zIndex = zIndex; }
        core_id GetObjectID() const { return objectID; }
        bool IsRunning() const { return running; }

        ProjectionMode mode;

        static GameObject* GetGameObjectByID(core_id id);

        
    };

    template <typename T>
    T* GameObject::GetComponent()
    {
        T* derived = nullptr;
        for (Component* com : components)
        {
            derived = dynamic_cast<T*>(com);
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
