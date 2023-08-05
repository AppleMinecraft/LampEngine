#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Core/Logger.h"
#include "Core/Camera.h"

namespace LampEngine {
	// The window class is the most important which handles glfw window creation
	class Window {
	public:
		/*
		* Creates glfw window and initializes glad.
		* @param title: Title of the window.
		* @param width: Width of the window.
		* @param height: Height of the window.
		*/
		Window(const char* title = "UntitledWindow", int width = 800, int height = 800);
		~Window();

		// Updates the window like: swap the window buffer, handles event, etc.
		// Usage: At end of every frame.
		void update() const;
		// Clears the color buffer, depth buffer, etc.
		// Usage: At start of every frame.
		void clear() const;
		// Closes the glfw window.
		void close() const;

		// Sets window title to give title.
		void setWindowTitle(const char* title);
		// Sets window size to given width and height.
		void setWindowSize(int width, int height);
		// Sets window size to given Vector2 size.
		void setWindowSize(glm::vec2 size);
		// Sets window background color to given r, g, b;
		void setWindowColor(float r, float g, float b);

		// Returns the GLFWwindow pointer
		GLFWwindow* getNativeWindow() const;
		// Returns the window title
		const char* getWindowTitle()  const;
		// Returns window size in Vector2
		glm::vec2 getWindowSize()   const;
		// Returns true is window is not closed.
		bool isRunning() const;

		// Static function used to get current window
		static Window* GetCurrentWindowInstance();
	public:
		glm::vec3 windowColor;
		// The pointer to current camera.
		Camera* camera = nullptr;
	private:
		GLFWwindow* m_Window;
		const char* m_Title;
	};
}
