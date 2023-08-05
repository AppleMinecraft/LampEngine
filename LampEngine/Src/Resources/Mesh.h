#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include "Buffers/VAO.h"
#include "Core/Shader.h"
#include "Resources/Texture.h"
#include "Resources/Material.h"
#include "Renderable/Renderable.h"

namespace LampEngine {

	//The Mesh class holds vertex positions, normals, UVs, and indices, and is responsible for generating all the necessary shaders and buffers.
	class Mesh : public Renderable {
	public:

		/*
		* The constructor creates shaders buffers and stores vertices and indices.
		* NOTE: Call the method loadTextures() after the constructor. 
		* @param name: Name of the mesh.
		* @param vertices: Vector of vertex(Positions, Normals, UVs) to be stored.
		* @param indices: Vector of indices to be stored.
		*/
		Mesh(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

		// This method loads all the essential textures from the material, including the base texture, roughness texture, and normal map texture.
		// This method must be called once after the constructor or if any texture changes in the material.
		void loadTextures(); 

		// This method renders the mesh.
		void render() override;

		// Returns the ID of mesh shader.
		Shader& getShader() override;

		// Returns the ID of Mesh VAO buffer.
		VAO& getVAO() override;
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
		Texture m_BaseTexture, m_RoughnessTexture;
		VAO m_VAO;
		Shader m_Shader;
	};
}
