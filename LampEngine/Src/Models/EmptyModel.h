#pragma once

#include <glad/glad.h>

namespace LampEngine {
	class EmptyModel {
	public:
		EmptyModel(GLuint vaoID, int verticesCount);

		GLuint getVAOID() const;
		int getVerticesCount() const;
	private:
		GLuint m_VAOID;
		int m_VerticesCount;
	};
}
