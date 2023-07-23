#include "Entity.h"

namespace LampEngine {
	Entity::Entity(TextureModel& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
		m_Model(model),
		position(position),
		rotation(rotation),
		scale(scale) 
	{
	}

	TextureModel& Entity::getModel() {
		return m_Model;
	}
}