#pragma once

#include <vector>
#include <glad/glad.h>

namespace LampEngine {

	// Element Buffer Object
	class EBO {
	public:
		// This class sent the indices to OpenGL to tell it how to draw the data
		EBO(std::vector<GLuint> indices);

		// Binds the Element Buffer Object
		void bind();

		// Returns the ID of Element Buffer Object
		GLuint getID();
	private:
		GLuint m_ID;
	};
}
