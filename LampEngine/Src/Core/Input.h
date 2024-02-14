#pragma once
#include <cstdint>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace LampEngine {
	enum class Key {
		PRESSED = GLFW_PRESS,
		RELEASED = GLFW_RELEASE,
	};

	enum class MouseMode {
		NORMAL = GLFW_CURSOR_NORMAL,
		HIDDEN = GLFW_CURSOR_HIDDEN,
		DISABLED = GLFW_CURSOR_DISABLED,
	};

	class Input {
	public:
		static Key GetKey(int key);
		static Key GetMouseButton(int button);

		static bool IsKeyPressed(int key);
		static bool IsKeyReleased(int key);

		static bool IsMouseButtonPressed(int button);
		static bool IsMouseButtonReleased(int button);

		static glm::vec2 GetMousePosition();
		static void SetMousePosition(glm::vec2 position);
		static void SetMousePosition(double x, double y);
		static void SetMouseMode(MouseMode mode);
	};
}
