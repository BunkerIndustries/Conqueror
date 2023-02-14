#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"

namespace core {

	class KeyPressedEvent : public Event {
	private:
		bool repeated;
		int key_code;
	public:
		KeyPressedEvent() = default;
		KeyPressedEvent(const int key_code, const int repeat_count)
			: repeated(repeat_count > 0), key_code(key_code) { }

		inline int getKeyCode() const { return key_code; }
		inline bool getRepeated() const { return repeated; }

		std::string toString() const override {
			std::stringstream string;
			string << "KeyPressedEvent: " << key_code << " | Repeated: " << repeated;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public Event {
	private:
		int key_code;
	public:
		KeyReleasedEvent() = default;
		KeyReleasedEvent(const int key_code)
			: key_code(key_code) { }

		inline int getKeyCode() const { return key_code; }

		std::string toString() const override {
			std::stringstream string;
			string << "KeyReleasedEvent: " << key_code;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public Event {
	private:
		int key_code;
	public:
		KeyTypedEvent() = default;
		KeyTypedEvent(const int key_code)
			: key_code(key_code) { }

		inline int getKeyCode() const { return key_code; }


		std::string toString() const override {
			std::stringstream string;
			string << "KeyPressedEvent: " << key_code;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

		EVENT_CLASS_TYPE(KeyTyped)
	};

	
}

