#include "Renderer.h"

namespace LampEngine {
	void Renderer::Clear() {
		glm::vec3 color = Window::GetCurrentWindowInstance()->getWindowColor();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, 1.0f);
	}
	void Renderer::Render(EmptyModel model) {
		glBindVertexArray(model.getVAOID());
		glDrawElements(GL_TRIANGLES, model.getVerticesCount(), GL_UNSIGNED_INT, 0);
	}
}