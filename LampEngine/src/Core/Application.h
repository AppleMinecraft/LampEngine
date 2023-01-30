#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Events/Event.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Core/Scene.h"

static LampEngine::Application* s_CurrentApplicationInstance;

namespace LampEngine
{
	class Application
	{
	public:
		Application(const char* ApplicationName, int WindowWidth, int WindowHeight);

		Window getWindow() const;
		Scene& getCurrentScene() const;

		bool isRunning() const;

		void setCurrentScene(Scene& scene);

		void update() const;
		void close() const;
	private:
		static void eventHandler(Event& e);
	private:
		Window m_Window;
		Scene* m_Scene;
	};

}