/*
* --------------------Window.h----------------------
* |No need to use this file manully the application|
* |class creates and updates window for you.       |
* --------------------------------------------------
*/
#pragma once

#include <string>
#include <functional>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Core/Log.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace LampEngine {

	class Window
	{
	public:
		using EventFn = std::function<void(Event&)>;
		EventFn CallbackFunc;
		Window(const char* title, int width, int height, EventFn callbackFunc);

		int getWidth() const;
		int getHeight() const;
		std::string getTitle() const;
		GLFWwindow* getNativeWindow() const;

		void setWidth(int width);
		void setHeight(int height);
		void setTitle(const char* title);

		bool isRunning() const { return !glfwWindowShouldClose(m_Window); }

		void clear() const;
		void update() const;
		void kill() const;

	private:
		std::string m_Title;
		GLFWwindow* m_Window;
	};

}
