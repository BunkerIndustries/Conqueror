#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"

#include "generic/GameObject.h"

namespace core {

    class Component {
    protected:
        GameObject* gameObject = nullptr;

    public:
        Component() = default;
    	virtual ~Component() = default;

        virtual void OnStart() { }
        virtual void OnStop() { }
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& event) { }
        virtual void OnImgui(float dt) { }

        GameObject* GetGameObject() const { return gameObject; }

        friend class GameObject;
    };

}