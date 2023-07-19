#pragma once
#include "Core/Texture.h"
#include "Models/EmptyModel.h"

namespace LampEngine {
	class TextureModel
	{
	public:
		TextureModel(GLuint textureID, EmptyModel model);

		GLuint getTextureID();
		EmptyModel& getEmptyModel();

		void bind();
	private:
		GLuint m_TextureID;
		EmptyModel m_Model;
	};
}
