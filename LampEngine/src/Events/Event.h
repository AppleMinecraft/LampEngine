/*
* ---------------------Event.h----------------------
* |Inspired a lot by Hazel GameEngine event system.|
* |           Visit: hazelengine.com               |
* --------------------------------------------------
*/
#pragma once
#include <string>
#include <functional>

namespace LampEngine {

	enum class EventType
	{
		None = 0,
		ApplicationCreated, ApplicationRender, ApplicationTick, ApplicationClosed,
		WindowClosed, WindowResize, WindowMove, WindowFocus, WindowLostFocus,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMove, MouseButtonPressed, MouseButtonReleased, MouseScroll
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = (1 << 0),
		EventCategoryInput       = (1 << 1),
		EventCategoryKeyboard    = (1 << 2),
		EventCategoryMouse       = (1 << 3),
		EventCategoryMouseButton = (1 << 4)
	};

#define SetupEventType(type) static EventType GetEventType() { return EventType::type; } \
								virtual EventType getEventType() const override { return EventType::type; }\
								virtual const char* getEventName() const override { return #type; }
#define SetupEventCategory(category) virtual int getEventCategory() const override { return category; }

	class Event
	{
	public:
		virtual const char* getEventName() const = 0;
		virtual EventType getEventType() const = 0;
		virtual int getEventCategory() const = 0;

		virtual std::string toString() const { return getEventName(); }

		bool isInCategory(EventCategory category)
		{
			return getEventCategory() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event):
			m_Event(event) {}

		template<typename T, typename F>
		void dispatch(F& func)
		{
			if (m_Event.getEventType() == T::GetEventType())
			{
				func(static_cast<T&>(m_Event));
			}
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

}