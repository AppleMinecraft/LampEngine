#include "Application.h"

namespace LampEngine
{
	Application::Application(const char* ApplicationName, int WindowWidth, int WindowHeight) :
		m_Window(ApplicationName, WindowWidth, WindowHeight, eventHandler)
	{
		if (s_CurrentApplicationInstance)
			return;
		s_CurrentApplicationInstance = this;
		ApplicationCreatedEvent event;
		eventHandler(event);
	}
	Window Application::getWindow() const
	{
		return m_Window;
	}

	bool Application::isRunning() const
	{
		return m_Window.isRunning();
	}

	void Application::close() const
	{
		m_Window.kill();
		ApplicationClosedEvent event;
		eventHandler(event);
		s_CurrentApplicationInstance = nullptr;
	}

	void Application::eventHandler(Event& e)
	{
		
		std::cout << e << "\n";
	}

	void Application::update() const
	{
		m_Scene->updateScene();
		m_Window.clear();
		m_Scene->renderScene();
		m_Window.update();
	}

	Scene& Application::getCurrentScene() const
	{
		return *m_Scene;
	}

	void Application::setCurrentScene(Scene& scene)
	{
		if (&scene)
			m_Scene = &scene;
	}
}