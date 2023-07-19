#pragma once
#include <glad/glad.h>
#include "Core/Logger.h"
#include "Models/EmptyModel.h"
#include "Models/TextureModel.h"

namespace LampEngine {
	class Loader {
	public:
		static TextureModel LoadTextureModel(Texture texture, GLfloat* vertices, int verticesSize, GLuint* indices, int indicesSize, GLfloat* uv, int uvSize);
		static EmptyModel   LoadEmptyModel(GLfloat* vertices, int verticesSize, GLuint* indices, int indicesSize, GLfloat* uv, int uvSize);
	private:
		static void       LoadVBO(int attributeNumber, GLfloat* data, int dataSize, int dataLength = 3, GLenum dataType = GL_FLOAT);
	};
}
