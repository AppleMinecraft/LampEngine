#include "Model.h"
#include "Core/Window.h"

namespace LampEngine {
	Model::Model(std::vector<Mesh*>& meshes) :
		m_Meshes(meshes) 
	{
		LOGinfo("Loading shaders and textures for meshes.");
		Shader shader("Res/Shaders/mesh_shader.vertex", "Res/Shaders/mesh_shader.fragment");
		for (Mesh* mesh : m_Meshes) {
			mesh->loadTextures();
			mesh->loadShader(shader);
		}
	}
	void Model::render() {
		for (Mesh* mesh: m_Meshes) {
			mesh->transform = transform;
			mesh->getShader().Uniform3v("lightColor", lightColor);
			mesh->getShader().Uniform3v("lightPos", lightPosition);
			mesh->render();
		}
	}
	void Model::destroy() {
		// Delete the meshes from memory
		for (Mesh* mesh : m_Meshes) {
			delete mesh;
		} 
		// Clear the vector of meshes
		m_Meshes.clear();
	}
	Mesh* Model::getMesh(int idx) {
		return m_Meshes[idx];
	}
}