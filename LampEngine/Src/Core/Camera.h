#pragma once

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Core/Window.h"
#include "Core/Entity.h"
#include "Core/Shader.h"

namespace LampEngine {
	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));

		void matrix(Entity& entity, Shader& shader);
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		float FOV = 45.0f;
	};
}
