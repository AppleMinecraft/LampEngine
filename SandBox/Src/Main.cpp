#include <LampEngine.h>

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f
};

GLfloat uv[] = {
	0, 0,
	0, 1,
	1, 1,
	1, 0 
};

GLuint indices[] = {
	0, 2, 1,
	0, 3, 2 
};

using namespace LampEngine;

int main() {
	Core::Init();
	Window window("LampEngine.SandBox", 1200, 720);
	Core::ImGui_Init(window);

	Camera camera(glm::vec3{0.0f, 0.0f, -5.0f});
	window.camera = &camera;

	// Object1
	Texture texture("Res/Textures/Texture.png", true);
	Shader shader("Res/Shaders/default_shader.vertex", "Res/Shaders/default_shader.fragment");
	TextureModel model = Loader::LoadTextureModel(texture, vertices, sizeof(vertices), indices, sizeof(indices), uv, sizeof(uv));
	Entity entity(model);

	shader.Uniform1i("textureSampler", 0);
	texture.free();

	while (window.isRunning()) {
		Renderer::Clear();
		Core::ImGui_NewFrame();

		// Object1
		shader.bind();
		Renderer::Render(entity, shader);

		Core::ImGui_Render();
		window.update();
	}

	return 0;
}