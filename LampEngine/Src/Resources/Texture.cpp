#include "Texture.h"

namespace LampEngine {
	Texture::Texture(Image& image, GLuint textureSlot, TextureSettings& textureSettings) :
		m_Slot(GL_TEXTURE0 + textureSlot)
	{
		// Gen Texture
		glGenTextures(1, &m_ID);
		glActiveTexture(m_Slot);
		bind();
		// Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureSettings.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureSettings.magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureSettings.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureSettings.wrapT);
		// Giving Data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Texture::bind() {
		glActiveTexture(m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
	GLuint Texture::getID() {
		return m_ID;
	}
}