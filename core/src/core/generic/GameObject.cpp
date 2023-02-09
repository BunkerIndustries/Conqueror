#include "_Core.h"

#include "generic/GameObject.h"
#include "generic/Component.h"
#include "generic/Transform.h"
#include "utils/DataPool.h"

#include "imgui/ImGuiLayer.h"
#include "event/Event.h"


namespace core {

    std::unordered_map<core::Component*, core::GameObject*> core::GameObject::CGMap;

    GameObject::GameObject(std::string name) {
        // create gameObject with name and create a standard transform object
        this->name = name;
        this->transform = Transform();
        this->zIndex = 0;
        this->displayMode = DataPool::DISPLAYMODE::PERSPECTIVE;

    }

    GameObject::GameObject(std::string name, Transform transform) {
        // create gameObject with name and a specific transform object
        // this is being called if you want specific coordinates (you would want this most of the time)
        this->name = name;
        this->transform = transform;
        this->zIndex = 0;
        this->displayMode = DataPool::DISPLAYMODE::PERSPECTIVE;

    }

    GameObject::GameObject(std::string name, Transform transform, DataPool::DISPLAYMODE displaymode)
    {
        this->name = name;
        this->transform = transform;
        this->zIndex = 0;
        this->displayMode = displaymode;

    }

    GameObject::~GameObject()
    {
        deleteComponents();
    }


    Component* GameObject::getComponent(std::string componentTypeID) {
        // iterate through components vector and return the component if it fits to the desired component type (renderer type)
        for (auto component : components)
        {
            if (componentTypeID == component->getTypeID())
            {
                return component;
            }
        }
        // if there is nothing, go to las vegas
        return nullptr;
    }

    bool GameObject::removeComponent(Component* delComponent) {
        // iterate through components array and delete the component regarding this sprite that equals to the desired component type
        for (int i = 0; i < components.size(); i++) {
            if (components[i] == delComponent) {
                if (running)
					components[i]->stop();
                delete components[i];
                components[i] = nullptr;
                return true;
            }
        }
        // return false if there was no such component
        return false;
    }
    // add components to component list, render them by calling 
    bool GameObject::addComponent(Component* component) {
        // if the component exists, set bool to true and
        // return false because it already exists

        // if it does not exist, create it at the next place that has not been used in the vector
        bool exists = false;
        for (auto i : components) {
            if (i == component) {
                exists = true;
            }
        }
        if (!exists) {
            components.push_back(component);
            CGMap[component] = this;
            return true;
        }
        return false;
    }

    void GameObject::update(float dt) {
        // update gameObject, in order to display moving changes
        for (auto component : components) {
            component->update(dt);
        }
    }

    void GameObject::start() {
        // start all components
        running = true;
        for (auto component : components) {
            component->start();
        }
    }

    void GameObject::stop()
    {
        running = false;
        for (auto component : components) {
            component->stop();
        }
    }

    void GameObject::deleteComponents() {
        // delete all components
        for (auto comp : components)
        {
            if (running) 
				comp->stop();
            delete comp;
            comp = nullptr;
        }
        components.clear();
    }

    std::string GameObject::getName() {
        // return name
        return this->name;
    }

    int GameObject::getZIndex() {
        // return ZIndex (screen priority)
        return this->zIndex;
    }

    void GameObject::setZIndex(int zIndex)
    {
        this->zIndex = zIndex;
    }

    void GameObject::imgui(float dt) {
        ImGui::Text("Generic stuff:");
        ImGui::SliderFloat(std::string("X:").c_str(), &this->transform.position.x, -10.0f, 10.0f, 0);
        ImGui::SliderFloat(std::string("Y:").c_str(), &this->transform.position.y, -10.0f, 10.0f, 0);
        ImGui::SliderFloat(std::string("Width:").c_str(), &this->transform.scale.x, 0.0f, 10.0f, 0);
        ImGui::SliderFloat(std::string("Height:").c_str(), &this->transform.scale.y, 0.0f, 10.0f, 0);
        
        for (auto component : components) {
            component->imgui(dt);
        }
    }

    void GameObject::event(Event& event)
    {
        for (Component* component : components)
        {
	        if (!event.handled)
	        {
                component->event(event);
	        }
        }
    }
}
