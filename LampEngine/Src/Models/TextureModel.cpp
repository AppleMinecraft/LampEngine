#include "TextureModel.h"

namespace LampEngine {
	TextureModel::TextureModel(GLuint textureID, EmptyModel model): m_TextureID(textureID), m_Model(model){
	}
	GLuint TextureModel::getTextureID() {
		return m_TextureID;
	}
	EmptyModel& TextureModel::getEmptyModel() {
		return m_Model;
	}
	void TextureModel::bind() {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
}