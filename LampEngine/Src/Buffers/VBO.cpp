#include "VBO.h"

namespace LampEngine {
	VBO::VBO(std::vector<Vertex>& vertices) {
		glGenBuffers(1, &m_ID);
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}
	void VBO::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}
	GLuint VBO::getID() {
		return m_ID;
	}
}