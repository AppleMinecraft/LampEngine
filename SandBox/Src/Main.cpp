#include <LampEngine.h>
using namespace LampEngine;

int main() {
	Core::Init();
	Window window("Diffuse Lighting", 1200, 720);
	Core::ImGui_Init(window);

	Camera camera(glm::vec3{0.0f, 0.0f, 5.0f});
	window.camera = &camera;

	float lightPosition[3] = { 0.0f, 0.0f, 0.0f };
	float lightColor[3] = { 1.0f, 1.0f, 1.0f };

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	float planeSize = 1.0f;
	vertices.push_back({ glm::vec3(-planeSize, 0.0f, -planeSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
	vertices.push_back({ glm::vec3(-planeSize, 0.0f, planeSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
	vertices.push_back({ glm::vec3(planeSize, 0.0f, planeSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(planeSize, 0.0f, -planeSize), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) });
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	Mesh* mesh = Mesh::CreateMesh("TestMesh", vertices, indices, Material());

	while (window.isRunning()) {
		window.clear();;

		Core::ImGui_NewFrame();
		ImGui::Begin("Lighting");
		ImGui::DragFloat3("LightPosition", lightPosition, 0.01f);
		ImGui::ColorEdit3("LightColor", lightColor);
		ImGui::End();

		mesh->getShader().Uniform3v("lightColor", glm::vec3(lightColor[0], lightColor[1], lightColor[2]));
		mesh->getShader().Uniform3v("lightPos", glm::vec3(lightPosition[0], lightPosition[1], lightPosition[2]));
		mesh->render();

		camera.input();

		Core::ImGui_Render();
		window.update();
	}

}