#include "Renderer.h"

namespace LampEngine {
	void Renderer::Clear() {
		glm::vec3 color = Window::GetCurrentWindowInstance()->getWindowColor();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, 1.0f);
		glViewport(0, 0, Window::GetCurrentWindowInstance()->getWindowSize().x, Window::GetCurrentWindowInstance()->getWindowSize().y);
	}
	void Renderer::Render(Entity& entity) {
		TextureModel& model = entity.getModel();

		glBindVertexArray(model.getEmptyModel().getVAOID());
		glDrawElements(GL_TRIANGLES, model.getEmptyModel().getVerticesCount(), GL_UNSIGNED_INT, 0);
	}
}