#include "Renderer.h"

namespace LampEngine {
	void Renderer::Clear() {
		Window* window = Window::GetCurrentWindowInstance();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(window->windowColor.r, window->windowColor.g, window->windowColor.b, 1.0f);
		glViewport(0, 0, window->getWindowSize().x, window->getWindowSize().y);
	}
	void Renderer::Render(Entity& entity, Shader& shader) {
		Window::GetCurrentWindowInstance()->camera->matrix(entity, shader);
		TextureModel& model = entity.getModel();

		glBindVertexArray(model.getEmptyModel().getVAOID());
		glDrawElements(GL_TRIANGLES, model.getEmptyModel().getVerticesCount(), GL_UNSIGNED_INT, 0);
	}
}