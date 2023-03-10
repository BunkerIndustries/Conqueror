#include "_Core.h"

#include "generic/GameObject.h"

#include "Application.h"
#include "generic/Component.h"
#include "generic/Transform.h"
#include "utils/DataPool.h"
#include "layer/Layer.h"

#include "component/SpriteRenderer.h"

#include "imgui/ImGuiLayer.h"
#include "utils/Core.h"


namespace core {

	std::unordered_map<core_id, GameObject*> GameObject::IDMap;

	void GameObject::StopComponentIndex(uint32_t index)
	{
        components[index]->stop();
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
        : name(name), transform(transform), mode(mode)
    {
        this->zIndex = 0;

        objectID = Core::RequestID();
        IDMap.emplace(objectID, this);
    }


    GameObject::~GameObject()
    {
        CORE_ASSERT(deleted, "you may not delete a GameObject, use the 'Delete' function of it instead");
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

    void GameObject::update(float dt)
	{
        // update gameObject, in order to display moving changes
        for (auto component : components) {
            if (component && !deleted) {
                component->update(dt);
            }
        }
    }

    void GameObject::start()
	{
        // start all components
        running = true;
        for (auto component : components) {
            component->start();
        }
    }

    void GameObject::stop()
    {
        running = false;
        for (auto component : components) 
        {
            component->stop();
        }
    }

    void GameObject::deleteComponents()
	{
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
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        return it != tagList.end();
    }


    void GameObject::event(Event& event)
    {
	    for (auto* component : components)
	    {
            component->event(event);
	    }
    }

    void GameObject::Delete()
    {
        this->running = false;
        this->deleted = true;
        transform.scale.x = 0.0f;
        transform.scale.y = 0.0f;
        if (auto* renderer = GetComponent<SpriteRenderer>()) renderer->update(Application::GetDT());
        layer->GetGameObjects()->erase(std::find(layer->GetGameObjects()->begin(), layer->GetGameObjects()->end(), this));
		for (size_t i = 0; i < components.size(); i++)
		{
			if (GetComponent<SpriteRenderer>() != components[i])
			{
                delete components[i];
                components.erase(i + components.begin());
			}
 		}
        delete this;
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

    GameObject* GameObject::GetGameObjectByID(core_id id)
    {
        CORE_ASSERT(id > 0, "invalid ID");
        if (IDMap.find(id) != IDMap.end()) {
            return IDMap.at(id);
        }
        return nullptr;
    }

    

}