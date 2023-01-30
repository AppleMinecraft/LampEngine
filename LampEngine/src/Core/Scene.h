#pragma once

#include "Object/Object.h"

namespace LampEngine {
	class Scene
	{
	public:
		Scene(const char* sceneName, Application& application);

		Object& getRoot() const;
		Application* getApplication() const;
		const char* getSceneName() const;

		void renderScene();
		void updateScene();

	private:
		Object m_RootObject;
		Application* m_Application;
		const char* m_SceneName;
	};
}
