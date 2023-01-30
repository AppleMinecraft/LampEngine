#include "Window.h"

// TODO: LampEngine: Add Debug Logs

namespace LampEngine {

	Window::Window(const char* title, int width, int height, EventFn callbackFunc) :
		CallbackFunc(callbackFunc)
	{
		glfwInit();
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		m_Title = title;
		if (!m_Window) {
			llog_fatal("Failed To Create GLFWwindow!");
			return;
		}
		glfwMakeContextCurrent(m_Window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			llog_fatal("Glad Failed To Load!");
			return;
		}

		glfwSetWindowUserPointer(m_Window, this);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);

			WindowResizeEvent event(width, height);
			data.CallbackFunc(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);
			WindowClosedEvent event;
			data.CallbackFunc(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key);
					data.CallbackFunc(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.CallbackFunc(event);
					break;
				}
				case GLFW_REPEAT:
				{
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.CallbackFunc(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.CallbackFunc(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.CallbackFunc(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.CallbackFunc(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			Window data = *(Window*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.CallbackFunc(event);
		});
	}
	int Window::getWidth() const
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);

		return width;
	}
	int Window::getHeight() const
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);

		return height;
	}
	std::string Window::getTitle() const
	{
		return m_Title;
	}
	GLFWwindow* Window::getNativeWindow() const
	{
		return m_Window;
	}
	void Window::setWidth(int width)
	{
		int _width, _height;
		glfwGetWindowSize(m_Window, &_width, &_height);
		glfwSetWindowSize(m_Window, width, _height);
	}
	void Window::setHeight(int height)
	{
		int _width, _height;
		glfwGetWindowSize(m_Window, &_width, &_height);
		glfwSetWindowSize(m_Window, _width, height);
	}
	void Window::setTitle(const char* title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, m_Title.c_str());
	}
	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	}
	void Window::update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void Window::kill() const
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
}