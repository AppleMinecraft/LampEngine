#pragma once
#include <string>
#include <glm/glm.hpp>

namespace LampEngine {

	// The material used by the mesh. It stores materials loaded from models or can be manually provided.
	struct Material {
		// The name of the material
		std::string name = "";
		// The base color of the mesh
		glm::vec3 baseColor = glm::vec3(1.0f);
		// The path to base texture
		std::string baseTexture = "";
		// The path to roughness texture
		std::string roughnessTexture = "";
		// The path to normal map texture
		std::string normalMapTexture = "";
		// The roughness value of the mesh, which should be within the range of 0 and 1.
		float roughness = 0.0;
	};
}