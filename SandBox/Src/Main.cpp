#include <LampEngine.h>
using namespace LampEngine;

int main() {
	Core::Init();
	Window window("LampEngine.SandBox", 1200, 720);
	Core::ImGui_Init(window);

	Camera camera(glm::vec3{0.0f, 1.0f, 5.0f});
	window.camera = &camera;

	Model model = Loader::LoadOBJModel("Res/Meshes/WoodTest.obj");
	model.rotation.y = 90;

	glm::vec3 lightPosition(0.0f, 0.4f, 0.0f);
	float lightColor[3] = { 1.0f, 1.0f, 1.0f };

	while (window.isRunning()) {
		window.clear();;
		Core::ImGui_NewFrame();

		model.lightColor = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);
		model.lightPosition = lightPosition;

		camera.input();
		model.render();

		ImGui::Begin("ImGui Window");
		ImGui::ColorEdit3("LightColor", lightColor);
		ImGui::End();

		Core::ImGui_Render();
		window.update();
	}

	model.destroy();
}