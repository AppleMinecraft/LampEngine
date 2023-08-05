#pragma once

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Core/Logger.h"
#include "Core/Window.h"

namespace LampEngine {

	// This class contains useful methods.
	class Core {
	public:
		// Loads OpenGL And LampEngine Logger etc.
		static void Init();
		// Call this after Core::Init if you want ImGui, this initilizes ImGui.
		static void ImGui_Init(Window& window);
		// Call this after Window::Clear to create ImGui new frame.
		static void ImGui_NewFrame();
		// Call this before Window::Update to render ImGui.
		static void ImGui_Render();
	};
}
