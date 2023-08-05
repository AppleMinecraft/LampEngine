#pragma once

#include <stb/stb_image.h>
#include <glad/glad.h>

#include "Core/Logger.h"
#include "Resources/Image.h"

namespace LampEngine {

	// Default TextureSettins with repeating image and linear filtering
	struct TextureSettings {
		GLuint wrapS = GL_REPEAT;
		GLuint wrapT = GL_REPEAT;
		GLuint minFilter = GL_LINEAR;
		GLuint magFilter = GL_LINEAR;
	};

	// The Texture class is responsible for creating and managing images using OpenGL.
	// It contains the Image class, which handles raw data, while Texture handles OpenGL-related operations.
	class Texture {
	public:
		Texture() = default;
		/*
		* @param image: The image data that OpenGL will use
		* @param textureSlot: This parameter represents the texture slot and can take values such as 1, 2, 3 etc.
		* @param textureSettings: The texture settings to use, specifying parameters like the filter, wrap to be used in OpenGL.
		*/
		Texture(Image& image, GLuint textureSlot = 0, TextureSettings& textureSettings = TextureSettings());

		// Used to bind the OpenGl Texture
		void bind();

		// Returns the texture ID that Opengl uses
		GLuint getID();
	private:
		GLuint m_Slot;
		GLuint m_ID;
	};
}
