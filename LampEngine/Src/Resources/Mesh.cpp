#include "Mesh.h"
#include <glm/glm.hpp>
#include "Core/Window.h"
#include "Buffers/VBO.h"
#include "Buffers/EBO.h"

#define _TEXTURE_BASE_SLOT 0
#define _TEXTURE_ROUGHNESS_SLOT 1

namespace LampEngine {
	Mesh::Mesh(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) :
		name(name),
		vertices(vertices),
		indices(indices),
		m_Shader("Res/Shaders/mesh_shader.vertex", "Res/Shaders/mesh_shader.fragment")
	{	
		m_VAO.bind();

		VBO vbo(vertices);
		EBO ebo(indices);

		m_VAO.linkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)(0 * sizeof(float))); // Vertex positions
		m_VAO.linkAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // Vertex normals
		m_VAO.linkAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // Vertex colors
		m_VAO.linkAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // Vertex UVs
	}
	void Mesh::loadTextures() {
		Image* WHITE_IMAGE = Image::GenerateWhiteImage();
		m_Shader.bind();

		// BASE TEXTURE
		if (material.baseTexture != "") {
			m_BaseTexture = Texture(Image(material.baseTexture, true), _TEXTURE_BASE_SLOT);
			m_BaseTexture.bind();
			m_Shader.Uniform1i("baseTexture", _TEXTURE_BASE_SLOT);
		}
		else { m_BaseTexture = Texture(*WHITE_IMAGE, _TEXTURE_BASE_SLOT); }

		// SPECULAR TEXTURE
		if (material.roughnessTexture != "") {
			m_RoughnessTexture = Texture(Image(material.roughnessTexture, true), _TEXTURE_ROUGHNESS_SLOT);
			m_RoughnessTexture.bind();
			m_Shader.Uniform1i("roughnessTexture", _TEXTURE_ROUGHNESS_SLOT);
		}
		else { m_RoughnessTexture = Texture(*WHITE_IMAGE, _TEXTURE_ROUGHNESS_SLOT); }
	}
	void Mesh::render() {
		Renderable::render();
		Camera* camera = Window::GetCurrentWindowInstance()->camera;

		// Bindings
		m_Shader.bind();
		m_BaseTexture.bind();
		m_RoughnessTexture.bind();

		camera->matrix(*this);

		// FLOATS
		m_Shader.Uniform1f("roughness", material.roughness);
		// COLORS
		m_Shader.Uniform3v("baseColor", material.baseColor);
		// POSITIONS
		m_Shader.Uniform3v("cameraPos", camera->position);
		m_VAO.bind();

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	Shader& Mesh::getShader() {
		return m_Shader;
	}
	VAO& Mesh::getVAO() {
		return m_VAO;
	}
}