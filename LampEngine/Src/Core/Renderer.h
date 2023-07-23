#pragma once

#include <glad/glad.h>

#include "Core/Window.h"
#include "Core/Entity.h"
#include "Core/Shader.h"
#include "Models/EmptyModel.h"
#include "Models/TextureModel.h"

namespace LampEngine {
	class Renderer
	{
	public:
		static void Clear();
		void static Render(Entity& entity, Shader& shader);
	};
}
