#include "Object.h"

#include "Core/Application.h"

namespace LampEngine
{
	Object::Object(const char* objectName, Application& application, Object* parent) :
		m_Application(&application),
		m_Visibility(true),
		m_ObjectName(objectName)
	{
		if (parent)
			parent->m_Childrens.push_back(this);
	}
	Application* Object::getApplication() const
	{
		return m_Application;
	}
	void Object::onUpdate()
	{
		for each (Object* object in m_Childrens)
			object->onUpdate();
		std::cout << getObjectName() << ": onUpdate()\n";
	}
	void Object::onRender()
	{
		for each (Object * object in m_Childrens) {
			if (object->m_Visibility)
				object->onRender();
		}
		std::cout << getObjectName() << ": onRender()\n";
	}
	void Object::hide()
	{
		setVisibility(false);
	}
	void Object::show()
	{
		setVisibility(true);
	}
	void Object::setVisibility(bool visibility)
	{
		m_Visibility = visibility;
	}
	void Object::setObjectName(const char* name)
	{
		m_ObjectName = name;
	}
	bool Object::getVisibility() const
	{
		return m_Visibility;
	}
	const char* Object::getObjectName() const
	{
		return m_ObjectName;
	}
}