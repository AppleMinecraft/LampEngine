#include "Window.h"

namespace LampEngine {
	static Window* CURRENT_WINDOW_INSTANCE = nullptr;

	Window::Window(const char* title, int width, int height) :
		m_Title(title),
		windowColor(0.0f, 0.05f, 0.1f) 
	{
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (!m_Window) {
			LOGcritical("GLFW Window {0}({1}, {2}) Failed To Load!", title, width, height);
			glfwTerminate();
			return;
		} LOGdebug("GLFW Window {0}({1}, {2}) Loaded.", title, width, height);

		glfwMakeContextCurrent(m_Window);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (!gladLoadGL()) {
			LOGcritical("Glad Has Failed To Load!");
			glfwTerminate();
			return;
		} LOGdebug("Glad Has Been Loaded.");

		CURRENT_WINDOW_INSTANCE = this;
	}
	Window::~Window() {
		CURRENT_WINDOW_INSTANCE = nullptr;
	}
	void Window::update() const {
		glViewport(0, 0, getWindowSize().x, getWindowSize().y);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void Window::prepare() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(windowColor.r, windowColor.g, windowColor.b, 1.0f);

		if (camera)
			camera->update();
	}
	void Window::close() const {
		glfwDestroyWindow(m_Window);
		glfwSetWindowShouldClose(m_Window, true);
		glfwTerminate();
		CURRENT_WINDOW_INSTANCE = nullptr;
	}
	void Window::setWindowTitle(const char* title) {
		m_Title = title;
		glfwSetWindowTitle(m_Window, title);
	}
	void Window::setWindowSize(int width, int height) {
		glfwSetWindowSize(m_Window, width, height);
	}
	void Window::setWindowSize(glm::vec2 size) {
		glfwSetWindowSize(m_Window, size.x, size.y);
	}
	void Window::setWindowColor(float r, float g, float b) {
		windowColor = glm::vec3(r, g, b);
	}
	GLFWwindow* Window::getNativeWindow() const {
		return m_Window;
	}
	const char* Window::getWindowTitle() const {
		return m_Title;
	}
	glm::vec2 Window::getWindowSize() const {
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return glm::vec2(width, height);
	}
	bool Window::isRunning() const {
		return !glfwWindowShouldClose(m_Window);
	}
	Window* Window::GetCurrentWindowInstance() {
		return CURRENT_WINDOW_INSTANCE;
	}
}