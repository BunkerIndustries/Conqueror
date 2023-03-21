#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"

namespace core {

	class KeyPressedEvent : public Event {
	private:
		bool repeated;
		int keyCode;
		int mods;
	public: 
		KeyPressedEvent(const int key_code, const int repeat_count, const int mods)
			: repeated(repeat_count > 0), keyCode(key_code), mods(mods) { }

		inline int getKeyCode() const { return keyCode; }
		inline bool getRepeated() const { return repeated; }
		inline bool IsModPressed(const int mod) const { return mods & mod; }

		std::string ToString() const override {
			std::stringstream string;
			string << "KeyPressedEvent: " << keyCode << " | Repeated: " << repeated;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public Event {
	private:
		int keyCode;
		int mods;
	public:
		KeyReleasedEvent(const int keyCode, const int mods)
			: keyCode(keyCode), mods(mods) { }

		inline int getKeyCode() const { return keyCode; }
		inline bool IsModPressed(const int mod) const { return mods & mod; }

		std::string ToString() const override {
			std::stringstream string;
			string << "KeyReleasedEvent: " << keyCode;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public Event {
	private:
		int keyCode;
	public:
		KeyTypedEvent() = default;
		KeyTypedEvent(const int key_code)
			: keyCode(key_code) { }

		inline int getKeyCode() const { return keyCode; }

		std::string ToString() const override {
			std::stringstream string;
			string << "KeyPressedEvent: " << keyCode;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

		EVENT_CLASS_TYPE(KeyTyped)
	};

	
}

