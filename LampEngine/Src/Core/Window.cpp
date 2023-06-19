#include "Window.h"

namespace LampEngine {
	Window::Window(const char* title, int width, int height) : m_Title(title), m_WindowColor(0.0f, 0.05f, 0.1f) {
		// Creating Window
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!m_Window) {
			LOGcritical("GLFW Window {0}({1}, {2}) Failed To Load!", title, width, height);
			glfwTerminate();
			return;
		} LOGdebug("GLFW Window {0}({1}, {2}) Loaded.", title, width, height);
		glfwMakeContextCurrent(m_Window);
		if (!gladLoadGL()) {
			LOGcritical("Glad Has Failed To Load!");
			glfwTerminate();
			return;
		} LOGdebug("Glad Has Been Loaded.");
	}
	void Window::update() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void Window::clear() {
		// TODO: get renderer as parameter and move this into renderer
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(m_WindowColor.r, m_WindowColor.g, m_WindowColor.b, 0);
	}
	void Window::close() {
		glfwDestroyWindow(m_Window);
		glfwSetWindowShouldClose(m_Window, true);
		glfwTerminate();
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
	void Window::setWindowColor(glm::vec3 color) {
		m_WindowColor = color;
	}
	void Window::setWindowColor(float r, float g, float b) {
		m_WindowColor = glm::vec3(r, g, b);
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
	glm::vec3 Window::getWindowColor() const {
		return m_WindowColor;
	}
	bool Window::isRunning() const {
		return !glfwWindowShouldClose(m_Window);
	}
}