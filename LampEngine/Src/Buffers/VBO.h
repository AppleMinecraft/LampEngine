#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace LampEngine {

	// The vertex struct which contain data for one vertex like: position, normal, color, uv
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 uv;
	};

	// Vertex Buffer Object
	class VBO {
	public:
		// The vertices to be sent to GPU.
		VBO(std::vector<Vertex>& vertices);

		// Binds the Vertex Buffer Object
		void bind();

		// Returns the ID of Vertex Buffer Object
		GLuint getID();
	private:
		GLuint m_ID;
	};
}
