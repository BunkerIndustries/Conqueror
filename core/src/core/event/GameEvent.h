#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"
#include "generic/GameObject.h"

namespace core
{

	class GameObjectEvent : public Event
	{
	public:
		GameObjectEvent() = default;
		GameObjectEvent(GameObject* gameObject)
			: gameObject(gameObject) { }

		inline GameObject* GetGameObject() const { return gameObject; }

		inline std::string ToString() const override {
			std::stringstream string;
			string << "GameObjectEvent: Name: " << gameObject->GetName() << " | CoreID: " << gameObject->GetCoreID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectPressed);

	protected:
		GameObject* gameObject = nullptr;
	};

	class GameObjectPressedEvent : public GameObjectEvent {
	public:
		GameObjectPressedEvent() = default;
		GameObjectPressedEvent(GameObject* gm)
			: GameObjectEvent(gm) { }


		inline std::string ToString() const override {
			std::stringstream string;
			string << "GameObjectPressedEvent: Name: " << gameObject->GetName() << " | ID: " << gameObject->GetCoreID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectPressed);
	};

	class GameObjectReleasedEvent : public GameObjectEvent {
	public:
		GameObjectReleasedEvent() = default;
		GameObjectReleasedEvent(GameObject* gm)
			: GameObjectEvent(gm) { }

		std::string ToString() const override {
			std::stringstream string;
			string << "GameObjectReleasedEvent: Name: " << gameObject->GetName() << " | ID: " << gameObject->GetCoreID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectReleased);
	};

	class GameObjectHoverBeginEvent : public GameObjectEvent {
	public:
		GameObjectHoverBeginEvent() = default;
		GameObjectHoverBeginEvent(GameObject* gm)
			: GameObjectEvent(gm) { }

		std::string ToString() const override {
			std::stringstream string;
			string << "GameObjectHoverBeginEvent: Name: " << gameObject->GetName() << " | ID: " << gameObject->GetCoreID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectHoverBegin);
	};

	class GameObjectHoverEndEvent : public GameObjectEvent {
	public:
		GameObjectHoverEndEvent() = default;
		GameObjectHoverEndEvent(GameObject* gm)
			: GameObjectEvent(gm) { }

		std::string ToString() const override {
			std::stringstream string;
			string << "GameObjectHoverEndEvent: Name: " << gameObject->GetName() << " | ID: " << gameObject->GetCoreID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectHoverEnd);
	};
}
