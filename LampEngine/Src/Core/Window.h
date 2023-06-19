#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Core/Logger.h"

namespace LampEngine {
	class Window {
	public:
		Window(const char* title = "UntitledWindow", int width = 800, int height = 800);
		
		void update();
		void clear();
		void close();
		void setWindowTitle(const char* title);
		void setWindowSize(int width, int height);
		void setWindowSize(glm::vec2 size);
		void setWindowColor(glm::vec3 color);
		void setWindowColor(float r, float g, float b);

		GLFWwindow* getNativeWindow() const;
		const char* getWindowTitle()  const;
		glm::vec2   getWindowSize()   const;
		glm::vec3   getWindowColor()  const;
		bool isRunning() const;
	private:
		GLFWwindow* m_Window;
		const char* m_Title;
		glm::vec3 m_WindowColor;
	};
}
