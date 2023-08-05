#include "EBO.h"

namespace LampEngine {
	EBO::EBO(std::vector<GLuint> indices) {
		glGenBuffers(1, &m_ID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}
	void EBO::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}
	GLuint EBO::getID() {
		return m_ID;
	}
}