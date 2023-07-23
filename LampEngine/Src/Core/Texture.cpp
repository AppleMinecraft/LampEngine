#include "Texture.h"

namespace LampEngine {
	Texture::Texture(const char* filename, bool flip, TextureSettings& textureSettings) : 
		m_TextureSettings(textureSettings) {
		stbi_set_flip_vertically_on_load(flip);
		m_Bytes = stbi_load(filename, &m_Width, &m_Heights, &m_Channels, 0);

		if (m_Bytes == nullptr)
			LOGerror("Failed To Load Texture '{0}'!", filename);
		else
			LOGdebug("Texture Had Been Loaded At '{0}' With Size Of {1}x{2} and flip={3}.", filename, m_Width, m_Heights, flip);
	}
	int Texture::getWidth() const {
		return m_Width;
	}
	int Texture::getHeight() const {
		return m_Heights;
	}
	int Texture::getColorChannels() const {
		return m_Channels;
	}
	unsigned char* Texture::getData() const {
		return m_Bytes;
	}
	TextureSettings Texture::getTextureSettings() const
	{
		return m_TextureSettings;
	}
	int Texture::getOpenGLColorChannels() const {
		int types[4] = { GL_R, GL_RG, GL_RGB, GL_RGBA };
		return types[m_Channels - 1];
	}
	void Texture::free() {
		stbi_image_free(m_Bytes);
	}
}