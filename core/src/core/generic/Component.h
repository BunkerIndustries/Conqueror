#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"

namespace core {

    class Component {
    public:
    protected:
        std::string typeID;
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
    };

}