#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Core/Logger.h"
#include "Core/Camera.h"

namespace LampEngine {
	class Window {
	public:
		Window(const char* title = "UntitledWindow", uint16_t width = 800, uint16_t height = 800);
		~Window();

		void update() const;
		void close() const;

		void setWindowTitle(const char* title);
		void setWindowSize(int width, int height);
		void setWindowSize(glm::vec2 size);
		void setWindowColor(float r, float g, float b);

		GLFWwindow* getNativeWindow() const;
		const char* getWindowTitle()  const;
		glm::vec2   getWindowSize()   const;
		bool isRunning() const;

		static Window* GetCurrentWindowInstance();
	public:
		glm::vec3 windowColor;
		Camera* camera = nullptr;
	private:
		GLFWwindow* m_Window;
		const char* m_Title;
	};
}
