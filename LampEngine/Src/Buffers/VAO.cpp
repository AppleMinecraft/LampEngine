#include "VAO.h"

namespace LampEngine {
	VAO::VAO() {
		glGenVertexArrays(1, &m_ID);
	}
	void VAO::linkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		VBO.bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
	}
	void VAO::bind() {
		glBindVertexArray(m_ID);
	}
	GLuint VAO::getID() {
		return m_ID;
	}
}
