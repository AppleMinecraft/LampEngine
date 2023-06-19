#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Logger.h"
#include "Utils/FileUtils.h"

namespace LampEngine {
	class Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader, bool readFromFile = true);

		void Uniform1f(const char* name, float value);
		void Uniform1i(const char* name, int value);
		void Uniform2v(const char* name, glm::vec2 value);
		void Uniform3v(const char* name, glm::vec3 value);
		void Uniform4v(const char* name, glm::vec4 value);
		void Uniform4x4mat(const char* name, glm::mat4x4 value);
		void bind();

		GLuint getShaderID();
	private:
		GLuint loadShader(const char* file, int type, bool readFromFile);
		GLuint m_ID;
	};
}
