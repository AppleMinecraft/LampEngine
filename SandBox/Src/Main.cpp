#include <LampEngine.h>

using namespace LampEngine;

GLfloat vertices[] = {
	-0.5f,  0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
};

GLuint indices[] = {
	0, 1, 3,
	3, 1, 2
};

int main() {
	Core::Init();
	Window window("LampEngine.SandBox");
	EmptyModel model = GraphicsLoader::LoadEmptyModel(vertices, sizeof(vertices), indices, sizeof(indices));
	Shader shader("Res/Shaders/default_shader.vertex", "Res/Shaders/default_shader.fragment");

	while (window.isRunning()) {
		Renderer::Clear();
		shader.bind();
		Renderer::Render(model);

		window.update();
	}

	return 0;
}