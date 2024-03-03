#include <LampEngine.h>
using namespace LampEngine;

int main() {
	Core::Init();
	Window window("Diffuse Lighting", 1200, 720);
	Core::ImGui_Init(window);

	FreeCamCamera camera;
	camera.transform.position.x = -4;

	window.camera = &camera;

	float lightPosition[3] = { 0.0f, 3.0f, 3.0f };
	float lightColor[3] = { 1.0f, 1.0f, 1.0f };

	Model model = Loader::LoadOBJModel("Res/Meshes/sphere.obj");

	while (window.isRunning()) {
		window.prepare();

		Core::ImGui_NewFrame();
		ImGui::Begin("Lighting");
		ImGui::DragFloat3("LightPosition", lightPosition, 0.01f);
		ImGui::ColorEdit3("LightColor", lightColor);
		ImGui::End();

		model.lightColor = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);
		model.lightPosition = glm::vec3(lightPosition[0], lightPosition[1], lightPosition[2]);
		model.render();

		Core::ImGui_Render();
		window.update();
	}

}