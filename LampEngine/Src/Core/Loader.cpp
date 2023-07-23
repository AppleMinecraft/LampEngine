#include "Loader.h"

namespace LampEngine {
	TextureModel Loader::LoadTextureModel(Texture& texture, GLfloat* vertices, uint32_t verticesSize, GLuint* indices, uint32_t indicesSize, GLfloat* uv, uint32_t uvSize) {
		EmptyModel model = Loader::LoadEmptyModel(vertices, verticesSize, indices, indicesSize, uv, uvSize);
		TextureSettings& settings = texture.getTextureSettings();
		GLuint textureID;

		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrapT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getWidth(), texture.getHeight(), 0, texture.getOpenGLColorChannels(), GL_UNSIGNED_BYTE, texture.getData());
		glGenerateMipmap(GL_TEXTURE_2D);

		return TextureModel(textureID, model);
	}
	EmptyModel Loader::LoadEmptyModel(GLfloat* vertices, uint32_t verticesSize, GLuint* indices, uint32_t indicesSize, GLfloat* uv, uint32_t uvSize) {
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		LoadVBO(0, vertices, verticesSize, 3, GL_FLOAT);
		LoadVBO(1, uv, uvSize, 2, GL_FLOAT);

		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

		int vertexCount = indicesSize / sizeof(int);

		LOGdebug("Loaded A EmptyModel With Vertex Count Of {0}.", vertexCount);
		return EmptyModel(vao, vertexCount);
	}
	void Loader::LoadVBO(uint8_t attributeNumber, GLfloat* data, uint32_t dataSize, uint8_t dataLength, GLenum dataType) {
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, dataLength, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(attributeNumber);
		LOGdebug("Loaded A Vertex Buffer Object With Attribute Number '{0}'.", attributeNumber);
	}
}