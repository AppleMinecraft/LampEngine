#include "Camera.h"
#include "Core/Window.h"
#include "Core/Input.h"

namespace LampEngine {
	Camera::Camera():
		m_Orientation(1.0f, 0.0f, 0.0f) { }

	Camera::Camera(Transform3D transform) :
		transform(transform),
		m_Orientation(1.0f, 0.0f, 0.0f) { }


	glm::vec3 Camera::getOrientation() {
		return m_Orientation;
	}

	void Camera::_matrix(Renderable& renderable) {
		// Bind the shader to set the uniform varibles
		Shader& shader = renderable.getShader();
		shader.bind();

		// Construction the Matrices
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		// Getting Window Size for Projection Matrix
		glm::vec2 windowSize = Window::GetCurrentWindowInstance()->getWindowSize();

		// ModelMatrix
		model = glm::translate(model, renderable.transform.position);
		applyRotation(model, renderable.transform.rotation);
		model = glm::scale(model, renderable.transform.scale);

		// ViewMatrix
		view = glm::lookAt(transform.position, transform.position + m_Orientation, UP);
		view = glm::rotate(view, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// ProjectionMatrix
		if (windowSize.x != 0.0f && windowSize.y != 0.0)
			proj = glm::perspective(glm::radians(FOV), (float)windowSize.x / windowSize.y, nearPlane , farPlane);

		// Setting the matrices in the shader
		shader.Uniform4x4mat("model", model);
		shader.Uniform4x4mat("view", view);
		shader.Uniform4x4mat("proj", proj);
	}

	void Camera::update() {
		// Calculate orientation
		glm::vec3 front;
		front.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		front.y = sin(glm::radians(transform.rotation.x));
		front.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		m_Orientation = glm::normalize(front);
	}
	
	void Camera::applyRotation(glm::mat4& matrix, glm::vec3 rotation) {
		// Rotation Constants
		const glm::vec3 ROTATION_X = glm::vec3(-1.0f,  0.0f,  0.0f);
		const glm::vec3 ROTATION_Y = glm::vec3( 0.0f, -1.0f,  0.0f);
		const glm::vec3 ROTATION_Z = glm::vec3( 1.0f,  0.0f,  1.0f);

		matrix = glm::rotate(matrix, glm::radians(rotation.x), ROTATION_X);
		matrix = glm::rotate(matrix, glm::radians(rotation.y), ROTATION_Y);
		matrix = glm::rotate(matrix, glm::radians(rotation.z), ROTATION_Z);
	}


	void FreeCamCamera::update() {
		Camera::update();

		Window* defaultWindow = Window::GetCurrentWindowInstance();
		GLFWwindow* window = defaultWindow->getNativeWindow();

		int width = defaultWindow->getWindowSize().x;
		int height = defaultWindow->getWindowSize().y;

		// Get the input and move the Camera
		{
			// Move Forward/Backward/Left/Right
			if (Input::IsKeyPressed(GLFW_KEY_W))
				transform.position += m_Speed * m_Orientation;
			if (Input::IsKeyPressed(GLFW_KEY_A))
				transform.position += m_Speed * -glm::normalize(glm::cross(m_Orientation, UP));
			if (Input::IsKeyPressed(GLFW_KEY_S))
				transform.position += m_Speed * -m_Orientation;
			if (Input::IsKeyPressed(GLFW_KEY_D))
				transform.position += m_Speed * glm::normalize(glm::cross(m_Orientation, UP));

			// Move Up/Down
			if (Input::IsKeyPressed(GLFW_KEY_E))
				transform.position += m_Speed * UP;
			if (Input::IsKeyPressed(GLFW_KEY_Q))
				transform.position += m_Speed * -UP;

			// Sprint
			if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
				m_Speed = sprintSpeed;
			else if (Input::IsKeyReleased(GLFW_KEY_LEFT_SHIFT))
				m_Speed = moveSpeed;
		}


		// Rotate the Camera by Mouse
		if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {

			// Hides mouse cursor
			Input::SetMouseMode(MouseMode::DISABLED);

			// Prevents Camera from Jumping on the First Click
			if (m_FirstClick) {
				Input::SetMousePosition(width / 2.0f, height / 2.0f);
				m_FirstClick = false;
			}

			// Get current mouse position
			glm::vec2 currentPos = Input::GetMousePosition();

			// Calculate the offset from the center of the window
			float xOffset = currentPos.x - (width / 2.0f);
			float yOffset = (height / 2.0f) - currentPos.y; // Reversed since y-coordinates go from bottom to top

			// Apply sensitivity to the offset
			xOffset *= mouseSensitivity;
			yOffset *= mouseSensitivity;

			// Update the rotation angles
			transform.rotation.x += yOffset;
			transform.rotation.y += xOffset;

			// Clamp vertical rotation to prevent flipping
			if (transform.rotation.x > 89.0f)
				transform.rotation.x = 89.0f;
			if (transform.rotation.x < -89.0f)
				transform.rotation.x = -89.0f;

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			Input::SetMousePosition(width / 2.0f, height / 2.0f);

		} else if (Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
			// Unhides cursor since camera is not looking around anymore
			Input::SetMouseMode(MouseMode::NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			m_FirstClick = true;
		}
	}

	FreeCamCamera::FreeCamCamera(Transform3D transform) :
		Camera(transform) { }
	FreeCamCamera::FreeCamCamera() :
		Camera() { }
}