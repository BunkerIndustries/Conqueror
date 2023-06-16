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
		GameObjectEvent, GameObjectPressed, GameObjectReleased, GameObjectHoverBegin, GameObjectHoverEnd
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

#define EVENT_CLASS_TYPE(type) static EventType GetStaticEventType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticEventType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// why do you take the same value twice and then compare it twice
		inline bool IsInCategory(const EventCategory category) const {
			return GetCategoryFlags() & category;
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
			if (event.GetEventType() == T::GetStaticEventType()) {
				event.handled = func(*static_cast<T*>(&event));
				return true;
			}
			return false;
		}
	};

	// basically print the string of event everytime ostream 'os' gets directed to cout
	inline std::ostream& operator<<(std::ostream& os, const Event& event) {
		return os << event.ToString();
	}
	using EventCallbackFunction = std::function<void(Event&)>;
}


