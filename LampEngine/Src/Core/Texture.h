#pragma once
#include <stb/stb_image.h>
#include <glad/glad.h>
#include "Core/Logger.h"

namespace LampEngine {

	struct TextureSettings {
		GLuint wrapS = GL_REPEAT;
		GLuint wrapT = GL_REPEAT;
		GLuint minFilter = GL_LINEAR;
		GLuint magFilter = GL_LINEAR;
	};

	class Texture {
	public:
		Texture(const char* filename, bool flip, TextureSettings& textureSettings = TextureSettings());

		int getWidth() const;
		int getHeight() const;
		int getColorChannels() const;
		int getOpenGLColorChannels() const;
		unsigned char* getData() const;
		TextureSettings getTextureSettings() const;

		void free();
	private:
		TextureSettings m_TextureSettings;
		unsigned char* m_Bytes;
		int m_Width, m_Heights, m_Channels;
	};
}
