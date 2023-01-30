/*
* ---------------ApplicationEvent.h-----------------
* |Inspired a lot by Hazel GameEngine event system.|
* |           Visit: hazelengine.com               |
* --------------------------------------------------
*/
#pragma once

#include <sstream>
#include "Events/Event.h"

namespace LampEngine {
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int getWidth() const { return m_Width; }
		unsigned int getHeight() const { return m_Height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		SetupEventType(WindowResize)
		SetupEventCategory(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;

		SetupEventType(WindowClosed)
		SetupEventCategory(EventCategoryApplication)
	};

	class ApplicationCreatedEvent : public Event
	{
	public:
		ApplicationCreatedEvent() = default;

		SetupEventType(ApplicationCreated)
		SetupEventCategory(EventCategoryApplication)
	};

	class ApplicationClosedEvent : public Event
	{
	public:
		ApplicationClosedEvent() = default;

		SetupEventType(ApplicationClosed)
		SetupEventCategory(EventCategoryApplication)
	};

	class ApplicationTickEvent : public Event
	{
	public:
		ApplicationTickEvent() = default;

		SetupEventType(ApplicationTick)
		SetupEventCategory(EventCategoryApplication)
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() = default;

		SetupEventType(ApplicationRender)
		SetupEventCategory(EventCategoryApplication)
	};
}