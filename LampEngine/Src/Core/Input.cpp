#include "Input.h"

#include <GLFW/glfw3.h>
#include <Core/Window.h>

namespace LampEngine {
	Key Input::GetKey(int key) {
		return (Key)glfwGetKey(Window::GetCurrentWindowInstance()->getNativeWindow(), key);
	}
	Key Input::GetMouseButton(int button) {
		return (Key)glfwGetMouseButton(Window::GetCurrentWindowInstance()->getNativeWindow(), button);
	}
	bool Input::IsKeyPressed(int key) {
		return GetKey(key) == Key::PRESSED;
	}
	bool Input::IsKeyReleased(int key) {
		return GetKey(key) == Key::RELEASED;
	}
	bool Input::IsMouseButtonPressed(int button) {
		return GetMouseButton(button) == Key::PRESSED;
	}
	bool Input::IsMouseButtonReleased(int button) {
		return GetMouseButton(button) == Key::RELEASED;
	}
	glm::vec2 Input::GetMousePosition() {
		double X, Y;
		glfwGetCursorPos(Window::GetCurrentWindowInstance()->getNativeWindow(), &X, &Y);
		return glm::vec2(X, Y);
	}
	void Input::SetMousePosition(glm::vec2 position) {
		glfwSetCursorPos(Window::GetCurrentWindowInstance()->getNativeWindow(), position.x, position.y);
	}
	void Input::SetMousePosition(double x, double y) {
		SetMousePosition(glm::vec2(x, y));
	}
	void Input::SetMouseMode(MouseMode mode) {
		glfwSetInputMode(Window::GetCurrentWindowInstance()->getNativeWindow(), GLFW_CURSOR, (int)mode);
	}
}