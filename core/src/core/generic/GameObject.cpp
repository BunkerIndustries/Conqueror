#include "_Core.h"

#include "generic/GameObject.h"

#include "Application.h"
#include "generic/Component.h"
#include "generic/Transform.h"
#include "utils/DataPool.h"
#include "layer/Layer.h"
#include "generic/Scene.h"

#include "component/SpriteRenderer.h"
#include "event/Input.h"
#include "event/KeyCodes.h"

#include "imgui/ImGuiLayer.h"
#include "utils/Core.h"


namespace core {

	void GameObject::StopComponentIndex(uint32_t index)
	{
        components[index]->OnStop();
	}

	void GameObject::DeleteComponentIndex(uint32_t index)
	{
        delete components[index];
	}

	void GameObject::SetLayer(Layer* layer)
	{
        this->layer = layer;
	}

	GameObject::GameObject(std::string name, Transform& transform, ProjectionMode mode)
        : Object(name, transform), mode(mode) { }


    GameObject::~GameObject()
    {
        this->deleted = true;
        if (layer) {
            std::vector<GameObject*>::iterator it = std::find(layer->GetGameObjects().begin(), layer->GetGameObjects().end(), this);
            if (it != layer->GetGameObjects().end())
            {
                layer->GetGameObjects().erase(it);
            }
        }
        const int componentSize = components.size();
        for (int i = 0; i < componentSize; i++)
        {
            if (components.size() <= 0) break;

            if (running)
                components[0]->OnStop();
            delete components[0];
            components.erase(components.begin());
        }
    }


    bool GameObject::AddComponent(Component* component)
	{
        for (const auto i : components) 
        {
            if (i == component) 
            {
                return false;
            }
        }
        components.push_back(component);
        component->gameObject = this;
        return true;
    }

    void GameObject::Update()
	{
        core_id id = coreID;
        // update gameObject, in order to display moving changes
        for (auto component : components) {
            if (component) {
                component->OnUpdate();
            }
            if (Core::IsDeleted(id)) return;
        }
		transform.Update();
    }

    void GameObject::Start()
	{
        // start all components
        running = true;
        for (auto component : components) {
            component->OnStart();
        }
    }

    void GameObject::Stop()
    {
        running = false;
        for (auto component : components) 
        {
            component->OnStop();
        }
    }

    void GameObject::DeleteComponents()
	{
        // delete all components
        for (auto comp : components)
        {
            if (running) 
				comp->OnStop();
            delete comp;
            comp = nullptr;
        }
        components.clear();
    }

    GameObject* GameObject::AddTag(std::string tag)
    {
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        if (std::find(tagList.begin(), tagList.end(), tag) != tagList.end())
        {
            LOG_CORE_WARN("Adding a tag to a GameObject which it already has: '" + tag + "'");
            return this;
        }
        tagList.emplace_back(tag);
        return this;
    }

    GameObject* GameObject::AddTag(std::initializer_list<std::string> tags)
    {
        for (std::string tag : tags) {
            std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
            AddTag(tag);
        }
        return this;
    }

    bool GameObject::RemoveTag(std::string tag)
    {
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        if (it == tagList.end())
        {
            LOG_CORE_WARN("Removing a tag from a GameObject which it doesn't have: '" + tag + "'");
            return false;
        }
        tagList.erase(it);
        return true;
    }

    bool GameObject::HasTag(std::string tag)
    {
        if (tagList.size() <= 0) return false;
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        return it != tagList.end();
    }


    void GameObject::OnEvent(Event& event)
    {
	    for (auto* component : components)
	    {
            component->OnEvent(event);
	    }
    }


	void GameObject::Imgui(float dt) {
		ImGui::Text("Transform:");
        float speed = 0.5f;
        if (Input::IsKeyPressed(KEY_LEFT_SHIFT) && Input::IsKeyPressed(KEY_LEFT_CONTROL))
            speed = 0.001f;
        else if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
            speed = 0.01f;
        
		ImGui::DragFloat(std::string("X:").c_str(), &this->transform.position.x, speed);
		ImGui::DragFloat(std::string("Y:").c_str(), &this->transform.position.y, speed);
		ImGui::DragFloat(std::string("Width:").c_str(), &this->transform.scale.x, speed);
		ImGui::DragFloat(std::string("Height:").c_str(), &this->transform.scale.y, speed);
        ImGui::DragFloat(std::string("Rotation:").c_str(), &this->transform.rotation, speed);
        

		for (auto component : components) {
		    component->OnImgui(dt);
		}
    }

    

    

}