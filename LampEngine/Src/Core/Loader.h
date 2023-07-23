#pragma once

#include <glad/glad.h>

#include "Core/Logger.h"
#include "Models/EmptyModel.h"
#include "Models/TextureModel.h"

namespace LampEngine {
	class Loader {
	public:
		static TextureModel LoadTextureModel(Texture& texture, GLfloat* vertices, uint32_t verticesSize, GLuint* indices, uint32_t indicesSize, GLfloat* uv, uint32_t uvSize);
		static EmptyModel   LoadEmptyModel(GLfloat* vertices, uint32_t verticesSize, GLuint* indices, uint32_t indicesSize, GLfloat* uv, uint32_t uvSize);
		static void         LoadVBO(uint8_t attributeNumber, GLfloat* data, uint32_t dataSize, uint8_t dataLength = 3, GLenum dataType = GL_FLOAT);
	};
}
