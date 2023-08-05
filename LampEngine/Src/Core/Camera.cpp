#include "Camera.h"
#include "Core/Window.h"

namespace LampEngine {
	Camera::Camera(glm::vec3 position, glm::vec3 rotation):
		position(position),
		rotation(rotation)
	{
	}

	void Camera::matrix(Renderable& renderable) {
		Shader& shader = renderable.getShader();
		shader.bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		glm::vec2 windowSize = Window::GetCurrentWindowInstance()->getWindowSize();

		// ModelMatrix
		model = glm::translate(model, renderable.position);
		applyRotation(model, renderable.rotation);
		model = glm::scale(model, renderable.scale);
		// ViewMatrix
		view = glm::lookAt(position, position + orientation, UP);
		// ProjectionMatrix
		proj = glm::perspective(glm::radians(FOV), (float)windowSize.x / windowSize.y, nearPlane , farPlane);

		shader.Uniform4x4mat("model", model);
		shader.Uniform4x4mat("view", view);
		shader.Uniform4x4mat("proj", proj);
	}
	glm::vec3 Camera::getCameraMoveDirection() {
		//view = glm::lookAt(position, position + Orientation, Up);
		float pitch = glm::radians(rotation.x);
		float yaw = glm::radians(rotation.y);

		// NOTE: might not be correct way to do i am not good at math
		glm::vec3 viewDirection(
		    sin(yaw) * cos(pitch),
			sin(pitch),
			cos(yaw) * cos(pitch)
		);
		return glm::normalize(viewDirection);
	}
	void Camera::applyRotation(glm::mat4& matrix, glm::vec3 rotation)
	{
		const glm::vec3 ROTATION_X = glm::vec3(-1.0f,  0.0f,  0.0f);
		const glm::vec3 ROTATION_Y = glm::vec3( 0.0f, -1.0f,  0.0f);
		const glm::vec3 ROTATION_Z = glm::vec3( 1.0f,  0.0f,  1.0f);

		matrix = glm::rotate(matrix, glm::radians(rotation.x), ROTATION_X);
		matrix = glm::rotate(matrix, glm::radians(rotation.y), ROTATION_Y);
		matrix = glm::rotate(matrix, glm::radians(rotation.z), ROTATION_Z);
	}

	void Camera::input() {
		Window* defaultWindow = Window::GetCurrentWindowInstance();
		GLFWwindow* window = defaultWindow->getNativeWindow();
		int width = defaultWindow->getWindowSize().x;
		int height = defaultWindow->getWindowSize().y;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position += speed * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position += speed * -glm::normalize(glm::cross(orientation, UP));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position += speed * -orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position += speed * glm::normalize(glm::cross(orientation, UP));
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			position += speed * UP;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			position += speed * -UP;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 0.05f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = 0.01f;
		}

		if (glfwGetKey(window, GLFW_KEY_F8) == GLFW_PRESS) {
			exit(0);
		}


		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = 100.0f * (float)(mouseY - (height / 2)) / height;
			float rotY = 100.0f * (float)(mouseX - (width / 2)) / width;

			// Calculates upcoming vertical change in the Orientation
			glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, UP)));

			// Decides whether or not the next vertical Orientation is legal or not
			if (abs(glm::angle(newOrientation, UP) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				orientation = newOrientation;
			}

			// Rotates the Orientation left and right
			orientation = glm::rotate(orientation, glm::radians(-rotY), UP);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}
}