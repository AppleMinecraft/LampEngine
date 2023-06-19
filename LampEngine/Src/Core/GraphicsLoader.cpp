#include "GraphicsLoader.h"

namespace LampEngine {
	EmptyModel GraphicsLoader::LoadEmptyModel(GLfloat* vertices, int verticesSize, GLuint* indices, int indicesSize) {
		// Creating Vertex Array Object
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Creating and Loading Vertex Buffer Object Into Vertex Array Object
		LoadVBO(0, vertices, verticesSize, 3, GL_FLOAT);

		// Creating and Loading Element Buffer Object
		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

		LOGdebug("Loaded A EmptyModel With {0} Vertices.", indicesSize / sizeof(int));
		return EmptyModel(vao, indicesSize / sizeof(int));
	}
	void GraphicsLoader::LoadVBO(int attributeNumber, GLfloat* data, int dataSize, int dataLength, GLenum dataType) {
		// Creating Vertex Buffer Object
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, dataLength, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		LOGdebug("Loaded A Vertex Buffer Object With Attribute Number '{0}'.", attributeNumber);
	}
}