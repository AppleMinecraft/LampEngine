#pragma once
#include <glad/glad.h>
#include "Models/EmptyModel.h"
#include "Core/Logger.h"

namespace LampEngine {
	class GraphicsLoader {
	public:
		static EmptyModel  LoadEmptyModel(GLfloat* vertices, int verticesSize, GLuint* indices, int indicesSize);

	private:
		static void       LoadVBO(int attributeNumber, GLfloat* data, int dataSize, int dataLength = 3, GLenum dataType = GL_FLOAT);
	};
}
