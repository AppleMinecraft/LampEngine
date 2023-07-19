#include "Camera.h"
namespace LampEngine {
	Camera::Camera(glm::vec3 position, glm::vec3 rotation): position(position), rotation(rotation) {
	}

	void Camera::matrix(Entity& entity, Shader& shader) {
		shader.bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		Window* window = Window::GetCurrentWindowInstance();

		// ModelMatrix
		model = glm::translate(model, entity.position);
		model = glm::rotate(model, entity.rotation.x, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, entity.rotation.y, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, entity.rotation.z, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::scale(model, entity.scale);
		// ViewMatrix
		view = glm::translate(view, glm::vec3(position));
		view = glm::rotate(view, rotation.x, glm::vec3(-1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, rotation.y, glm::vec3(0.0f, -1.0f, 0.0f));
		view = glm::rotate(view, rotation.z, glm::vec3(0.0f, 0.0f, -1.0f));
		// ProjectionMatrix
		proj = glm::perspective(glm::radians(FOV), (float)window->getWindowSize().x / window->getWindowSize().y, 0.1f, 100.0f);

		shader.Uniform4x4mat("model", model);
		shader.Uniform4x4mat("view", view);
		shader.Uniform4x4mat("proj", proj);
	}
}