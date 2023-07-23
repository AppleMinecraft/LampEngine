#pragma once

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Core/Logger.h"
#include "Core/Window.h"

namespace LampEngine {
	class Core {
	public:
		/// <summary>
		/// Loads OpenGL And LampEngine Logger etc.
		/// </summary>
		static void Init();
		static void ImGui_Init(Window& window);
		static void ImGui_NewFrame();
		static void ImGui_Render();
	};
}
