#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"

#include "generic/GameObject.h"

namespace core {

    class Component {
    protected:
        std::string typeID;
        GameObject* gameObject = nullptr;

    public:
        Component(std::string typeID)
	        :typeID(typeID) { }
        virtual ~Component() = default;

    	std::string getTypeID() const { return typeID; }

        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void update(float dt) = 0;
        virtual void event(Event& event) = 0;
        virtual void imgui(float dt) { }

        GameObject* GetGameObject() const { return gameObject; }

        friend class GameObject;
    };

}