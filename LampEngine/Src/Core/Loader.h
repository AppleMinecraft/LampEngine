#pragma once

#include <glad/glad.h>

#include "Core/Logger.h"
#include "Resources/Mesh.h"
#include "Renderable/Model.h"
#include "Utils/FileUtils.h"
#include "Utils/_OBJLoader.h"

namespace LampEngine {

	// Loader class makes it easy to load Model, etc.
	class Loader {
	public:
		// Loads obj model form path and returns Model class with all the meshes
		static Model LoadOBJModel(std::string path);
	};
}
