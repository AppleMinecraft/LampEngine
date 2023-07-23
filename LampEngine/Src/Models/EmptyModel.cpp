#include "EmptyModel.h"

namespace LampEngine {
	EmptyModel::EmptyModel(GLuint vaoID, int verticesCount) :
		m_VAOID(vaoID),
		m_VerticesCount(verticesCount)
	{
	}
	GLuint EmptyModel::getVAOID() const {
		return m_VAOID;
	}
	int EmptyModel::getVerticesCount() const {
		return m_VerticesCount;
	}
}