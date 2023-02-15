#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"
#include "generic/GameObject.h"

namespace core
{
	class GameObjectPressedEvent : public Event {
	private:
		GameObject* gameObject;
	public:
		GameObjectPressedEvent() = default;
		GameObjectPressedEvent(GameObject* gameObject)
			: gameObject(gameObject) { }

		inline GameObject* GetGameObject() const { return gameObject; }

		std::string toString() const override {
			std::stringstream string;
			string << "GameObjectPressedEvent: Name:" << gameObject->getName() << " | ID: " << gameObject->GetObjectID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectPressed);
	};

	class GameObjectReleasedEvent : public Event {
	private:
		GameObject* gameObject;
	public:
		GameObjectReleasedEvent() = default;
		GameObjectReleasedEvent(GameObject* gameObject)
			: gameObject(gameObject) { }

		inline GameObject* GetGameObject() const { return gameObject; }

		std::string toString() const override {
			std::stringstream string;
			string << "GameObjectReleasedEvent: Name:" << gameObject->getName() << " | ID: " << gameObject->GetObjectID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectReleased);
	};

	class GameObjectHoverBeginEvent : public Event {
	private:
		GameObject* gameObject;
	public:
		GameObjectHoverBeginEvent() = default;
		GameObjectHoverBeginEvent(GameObject* gameObject)
			: gameObject(gameObject) { }

		inline GameObject* GetGameObject() const { return gameObject; }

		std::string toString() const override {
			std::stringstream string;
			string << "GameObjectHoverBeginEvent: Name:" << gameObject->getName() << " | ID: " << gameObject->GetObjectID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectHoverBegin);
	};

	class GameObjectHoverEndEvent : public Event {
	private:
		GameObject* gameObject;
	public:
		GameObjectHoverEndEvent() = default;
		GameObjectHoverEndEvent(GameObject* gameObject)
			: gameObject(gameObject) { }

		inline GameObject* GetGameObject() const { return gameObject; }

		std::string toString() const override {
			std::stringstream string;
			string << "GameObjectHoverEndEvent: Name:" << gameObject->getName() << " | ID: " << gameObject->GetObjectID();
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryGameObject | EventCategoryGame);

		EVENT_CLASS_TYPE(GameObjectHoverEnd);
	};
}
