#include "Scene.h"

namespace LampEngine {
	Scene::Scene(const char* sceneName, Application& application) :
		m_RootObject(sceneName, application),
		m_Application(&application),
		m_SceneName(sceneName)
	{

	}

	Object& Scene::getRoot() const
	{
		return (Object&)m_RootObject;
	}
	Application* Scene::getApplication() const
	{
		return m_Application;
	}
	const char* Scene::getSceneName() const
	{
		return m_SceneName;
	}
	void Scene::renderScene()
	{
		if (m_RootObject.getVisibility())
			m_RootObject.onRender();
	}
	void Scene::updateScene()
	{
		m_RootObject.onUpdate();
	}
}