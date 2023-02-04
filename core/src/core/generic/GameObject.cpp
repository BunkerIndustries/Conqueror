#include "_Core.h"

#include "generic/GameObject.h"
#include "generic/Component.h"
#include "generic/Transform.h"
#include "utils/DataPool.h"

#include "imgui/ImGuiLayer.h"



namespace core {

    std::unordered_map<Component*, GameObject*> GameObject::CGMap;

    GameObject::GameObject(std::string id, Transform transform, DisplayMode displaymode)
    {
        this->id = id;
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
        for (auto component : components) {
            component->start();
        }
    }

    void GameObject::deleteComponents() {
        // delete all components
        for (auto comp : components)
        {
            comp->stop();
            delete comp;
            comp = nullptr;
        }
        components.clear();
    }

    std::string GameObject::getStringID() {
        // return id
        return this->id;
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
        ImGui::Text("Transform: ");
        ImGui::SliderFloat(std::string("X:").c_str(), &this->transform.position.x, -10.0f, 10.0f, 0);
        ImGui::SliderFloat(std::string("Y:").c_str(), &this->transform.position.y, -10.0f, 10.0f, 0);
        ImGui::SliderFloat(std::string("Width:").c_str(), &this->transform.scale.x, 0.0f, 10.0f, 0);
        ImGui::SliderFloat(std::string("Height:").c_str(), &this->transform.scale.y, 0.0f, 10.0f, 0);
        
        for (auto component : components) {
            component->imgui(dt);
        }
    }

}