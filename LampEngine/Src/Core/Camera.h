#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Core/Shader.h"
#include "Renderable/Renderable.h"
#include "Utils/Transform.h"

namespace LampEngine {
	class Camera {
	public:
		Camera();
		/*
		* @param transform: Transform of the camera.
		*/
		Camera(Transform3D transform);

		// Returns the Orientation of the camera
		glm::vec3 getOrientation();
		virtual void update();

		Transform3D transform;
		// Camera Settings
		float FOV = 45.0f, nearPlane = 0.1f, farPlane = 1000.0f;
		const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

		// NOTE: This function is called automatically by some internal class.
		void _matrix(Renderable& renderable);
	protected:
		// A helper function applies x,y,z rotation to a matrix.
		void applyRotation(glm::mat4& matrix, glm::vec3 rotation);
		glm::vec3 m_Orientation;
	};

	// A FreeCamCamera class to show how to create custom camera and provide a built-in camera to see and move around 
	// This class is made with the help of VictorGordan OpenGL Camera.
	class FreeCamCamera : public Camera {
	public:
		FreeCamCamera();
		FreeCamCamera(Transform3D transform);

		void update() override;

		float moveSpeed = 0.01f;
		float sprintSpeed = 0.05f;
		float mouseSensitivity = 0.3f;
	private:
		float m_Speed = moveSpeed;
		bool m_FirstClick = true;
	};
}
