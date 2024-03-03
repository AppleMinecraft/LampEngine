#pragma once

#include <vector>
#include "Resources/Mesh.h"
#include "Utils/Transform.h"

namespace LampEngine {

	// This model class contains a array of meshes which can be rendered bu calling Model::render(); method
	class Model {
	public:
		/*
		* @param meshes: the vector of mesh pointers to be stored.
		*/
		Model(std::vector<Mesh*>& meshes);

		// Renders all the meshes in the model
		void render();
		// Destroyed all the meshes in the model
		void destroy();

		// Returns a pointer to mesh from the given index.
		Mesh* getMesh(int idx);
	public:
		Transform3D transform;
		// TODO: manage lightning
		glm::vec3 lightColor = glm::vec3(1.0f), lightPosition = glm::vec3(0.0f);
	protected:
		std::vector<Mesh*> m_Meshes;
	};
}
