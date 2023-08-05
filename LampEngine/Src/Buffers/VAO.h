#pragma once

#include <glad/glad.h>
#include "Buffers/VBO.h"

namespace LampEngine {
	// Vertex Array Object
	class VAO {
	public:
		VAO();

		/*
		* @param VBO: The vbo from which the data will be linked.
		* @param layout: The attribute number of data to sent to shader.
		* @param numComponents: Number of components of data, For Example: 2 for vec2, 3 for vec3, and 4 for vec4.
		* @param type: The type of data to send, most common type is GL_FLOAT
		* @param stride: The size of the data set
		*/
		void linkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		// Binds the Vertex Array Object
		void bind();

		// Retuns the ID of Vertex Array Object
		GLuint getID();
	private:
		GLuint m_ID;
	};
}
