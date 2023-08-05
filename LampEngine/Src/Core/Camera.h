#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Core/Shader.h"
#include "Renderable/Renderable.h"

/*
* ------------------------------------------------------------------------------------- *
*   NOTE:																			    *
*  	   This class does not conatin any doc because it it about to go throught a rework. *
* ------------------------------------------------------------------------------------- *
*/

namespace LampEngine {
	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));

		float speed = 0.01f;
		bool firstClick = true;
		void input();

		void matrix(Renderable& renderable);
		glm::vec3 getCameraMoveDirection();
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		float FOV = 45.0f, nearPlane = 0.1f, farPlane = 10000.0f;
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	private:
		void applyRotation(glm::mat4& matrix, glm::vec3 rotation);
	};
}
