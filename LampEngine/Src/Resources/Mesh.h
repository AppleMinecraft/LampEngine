#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include "Buffers/VAO.h"
#include "Core/Shader.h"
#include "Resources/Texture.h"
#include "Resources/Material.h"
#include "Renderable/Renderable.h"

#define _TEXTURE_BASE_SLOT 0
#define _TEXTURE_ROUGHNESS_SLOT 1
#define _TEXTURE_NORMALMAP_SLOT 2

namespace LampEngine {

	//The Mesh class holds vertex positions, normals, UVs, and indices, and is responsible for generating all the necessary shaders and buffers.
	class Mesh : public Renderable {
	public:

		/*
		* The constructor creates buffers and stores vertices and indices.
		* NOTE: Call the method loadTextures() after the constructor.
		* NOTE: Call the method loadShader(Shader) after the constructor.
		* @param name: Name of the mesh.
		* @param vertices: Vector of vertex(Positions, Normals, UVs) to be stored.
		* @param indices: Vector of indices to be stored.
		*/
		Mesh(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

		// This method loads a white texture if a texture is null in material, including the base texture, roughness texture, and normal map texture.
		// This method must be called once after the constructor.
		void loadTextures();
		// This method loads the shader provided the the mesh.
		// This method must be called once after the constructor.
		void loadShader(Shader shader);

		// This method renders the mesh.
		void render() override;

		// Returns the ID of mesh shader.
		Shader& getShader() override;

		// Returns the ID of Mesh VAO buffer.
		VAO& getVAO() override;

		// Calls the mesh constructor and loads shaders and textures.
		static Mesh* CreateMesh(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material);
	public:
		// The name of the mesh.
		std::string name;
		// The stored vector of vertices
		std::vector<Vertex> vertices;
		// The stored vector of indices
		std::vector<GLuint> indices;
		// The material assigned the the meah
		Material material;
	private:
		VAO m_VAO;
		Shader m_Shader;
	};
}
