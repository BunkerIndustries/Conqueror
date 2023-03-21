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

        virtual void OnStart() = 0;
        virtual void OnStop() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& event) = 0;
        virtual void OnImgui(float dt) { }

        GameObject* GetGameObject() const { return gameObject; }

        friend class GameObject;
    };

}