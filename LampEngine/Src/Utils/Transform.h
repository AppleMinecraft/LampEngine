#pragma once

#include <glm/glm.hpp>

namespace LampEngine {
	class Transform3D {
	public:
		Transform3D(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f)) :
			position(position),
			rotation(rotation),
			scale(scale) { }

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}
