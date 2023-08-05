#include "Loader.h"

namespace LampEngine {
	Model Loader::LoadOBJModel(std::string path) {
		// Loading OBJ Loader
		OBJLoader loader;
		bool success = loader.loadFile(path);
		if (success == false) {
			LOGerror("Failed to load OBJ file at '{}': File is not in .obj or does not exists.", path);
		} else LOGdebug("Loaded OBJ file at '{}'", path);

		// Creting Model
		Model model = Model(loader.LoadedMeshes);
		return model;
	}
}