#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Transform.h"
#include "utils/DataPool.h"
#include "event/Event.h"

namespace core {

    class Component;

    class CORE_API GameObject {
    private:
        std::string name;
        std::vector<Component*> components;
        int zIndex;

        bool running = false;

    public:
        Transform transform;
        GameObject(std::string name);
        GameObject(std::string name, Transform transform);
        GameObject(std::string name, Transform transform, DataPool::DISPLAYMODE displaymode);
        ~GameObject();

        Component* getComponent(std::string componentTypeID);
        bool removeComponent(Component* component);
        bool addComponent(Component* component);

        void update(float dt);
        void start();
        void stop();
        void imgui(float dt);
        void event(Event& event);

        void deleteComponents();

        std::string getName();
        int getZIndex();
        void setZIndex(int zIndex);
        bool IsRunning() const { return running; }

        DataPool::DISPLAYMODE displayMode;
    };

    
}