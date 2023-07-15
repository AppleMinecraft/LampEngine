#pragma once

#include <glad/glad.h>
#include "Core/Window.h"
#include "Models/EmptyModel.h"

namespace LampEngine {
	class Renderer
	{
	public:
		static void Clear();
		void static Render(EmptyModel model);
	};
}
