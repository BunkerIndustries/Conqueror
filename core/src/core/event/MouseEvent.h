#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"

//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

namespace core {
	class MouseButtonPressedEvent : public Event {
	private:
		int button;

	public:
		MouseButtonPressedEvent() = default;
		MouseButtonPressedEvent(int button)
			:button(button) { }

		inline int getButton() const { return button; }

		std::string toString() const override {
			std::stringstream string;
			string << "MouseButtonPressedEvent: " << button;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class MouseButtonReleasedEvent : public Event {
	private:
		int button;

	public:
		MouseButtonReleasedEvent() = default;
		MouseButtonReleasedEvent(int button)
			:button(button) { }

		inline int getButton() const { return button; }

		std::string toString() const override {
			std::stringstream string;
			string << "MouseButtonReleasedEvent: " << button;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class MouseMovedEvent : public Event {
	private:
		float mouseX, mouseY;

	public:
		MouseMovedEvent() = default;
		MouseMovedEvent(const float x, const float y)
			: mouseX(x), mouseY(y) { }

		inline float getX() const { return mouseX; }
		inline float getY() const { return mouseY; }

		std::string toString() const override {
			std::stringstream string;
			string << "MouseMovedEvent X: " << mouseX << " Y: " << mouseY;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		EVENT_CLASS_TYPE(MouseMoved)
	};

	class MouseScrolledEvent : public Event
	{
	private:
		float xOff;
		float yOff;

	public:
		MouseScrolledEvent() = default;
		MouseScrolledEvent(float xOff, float yOff)
			: xOff(xOff), yOff(yOff) { }

		inline float getXOffset() const { return xOff; }
		inline float getYOffset() const { return yOff; }

		std::string toString() const override {
			std::stringstream string;
			string << "MouseScrolledEvent X-Offset: " << xOff << " Y: " << yOff;
			return string.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		EVENT_CLASS_TYPE(MouseScrolled)
	};


}