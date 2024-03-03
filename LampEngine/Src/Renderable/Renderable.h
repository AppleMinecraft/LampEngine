#pragma once

#include <glm/glm.hpp>
#include "Buffers/EBO.h"
#include "Buffers/VAO.h"
#include "Buffers/VBO.h"
#include "Core/Shader.h"
#include "Utils/Transform.h"

namespace LampEngine {

	// Culling Mode used by the renderable
	enum class CULL_MODE {
		NO_CULL,
		FRONT_CULL,
		BACK_CULL,
	};

	// This class serves as the base class for all renderable objects.
	// It includes properties such as the object's position, rotation, and other attributes like cull mode, depth test, etc.
	class Renderable {
	public:
		Renderable();

		// The render function is virtual and can be overridden by derived classes.
		// When overridden, it must also call the base implementation to apply important rendering settings like cull face and depth test.
		// Like this Renderable::render();
		virtual void render();

		// Returns the shader ID
		virtual Shader& getShader() = 0;
		// Return the VAO ID
		virtual VAO& getVAO() = 0;
	public:
		Transform3D transform;
		CULL_MODE cullMode;
		bool depthTest = true;
	};
}
