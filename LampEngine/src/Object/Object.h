#pragma once

#include <vector>


namespace LampEngine
{
	class Application;

	class Object
	{
	public:
		Object(const char* objectName, Application& application, Object* parent = nullptr);

		Application* getApplication() const;

		virtual void onUpdate();
		virtual void onRender();

		void hide();
		void show();

		void setVisibility(bool visibility);
		void setObjectName(const char* name);

		bool getVisibility() const;
		const char* getObjectName() const;
	protected:
		bool m_Visibility;
		std::vector<Object*> m_Childrens;
		const char* m_ObjectName;
	private:
		Application* m_Application;
	};
}
