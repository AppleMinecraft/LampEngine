#include "Core.h"
#include <GLFW/glfw3.h>
#include "Core/Logger.h"

namespace LampEngine {
	namespace Core {
		void Init() {
			Logger::Init();
			if (!glfwInit()) {
				LOGcritical("GLFW Has Failed To Load.");
			} LOGdebug("GLFW Has Been Loaded.");
		}
	}
}
