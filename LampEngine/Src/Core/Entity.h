#pragma once

#include "Models/TextureModel.h"
#include "glm/glm.hpp"

namespace LampEngine {
	class Entity
	{
	public:
		Entity(TextureModel& model, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0));

		TextureModel& getModel() ;
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	private:
		TextureModel m_Model;
	};
}
