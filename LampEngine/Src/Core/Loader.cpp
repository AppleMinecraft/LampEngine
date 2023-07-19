#include "Loader.h"

namespace LampEngine {
	TextureModel Loader::LoadTextureModel(Texture texture, GLfloat* vertices, int verticesSize, GLuint* indices, int indicesSize, GLfloat* uv, int uvSize) {

		EmptyModel model = Loader::LoadEmptyModel(vertices, verticesSize, indices, indicesSize, uv, uvSize);
		TextureSettings settings = texture.getTextureSettings();
		GLuint id;

		glGenTextures(1, &id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrapT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getWidth(), texture.getHeight(), 0, texture.getOpenGLColorChannels(), GL_UNSIGNED_BYTE, texture.getData());
		glGenerateMipmap(GL_TEXTURE_2D);

		return TextureModel(
			id,
			model
		);
	}
	EmptyModel Loader::LoadEmptyModel(GLfloat* vertices, int verticesSize, GLuint* indices, int indicesSize, GLfloat* uv, int uvSize) {
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
	void Loader::LoadVBO(int attributeNumber, GLfloat* data, int dataSize, int dataLength, GLenum dataType) {
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, dataLength, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(attributeNumber);
		LOGdebug("Loaded A Vertex Buffer Object With Attribute Number '{0}'.", attributeNumber);
	}
}