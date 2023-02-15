#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {
	
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		GameObjectPressed, GameObjectReleased, GameObjectHoverBegin, GameObjectHoverEnd
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyBoard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
		EventCategoryGame			= BIT(5),
		EventCategoryGameObject		= BIT(6)
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticEventType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticEventType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class CORE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(const EventCategory category) const {
			return getCategoryFlags() & category;
		}

		bool handled = false;
	};

	class EventDispatcher {
	private:
		Event& event;
	public:
		EventDispatcher(Event& event) 
			: event(event) { }

		template <typename T> 
		bool dispatch(std::function<bool(T&)> func) {
			if (event.getEventType() == T::getStaticEventType()) {
				event.handled = func(*static_cast<T*>(&event));
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event) {
		return os << event.toString();
	}
	using EventCallbackFunction = std::function<void(Event&)>;
}


