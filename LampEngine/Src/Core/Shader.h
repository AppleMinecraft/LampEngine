#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Logger.h"
#include "Utils/FileUtils.h"

namespace LampEngine {

	// The shader class manages OpenGL shaders.
	class Shader {
	public:
		Shader() = default;
		/*
		* @param vertexShader: This can be the path to vertex shader file or the vertexShader depending on readFromFile parameter
		* @param vertexShader: This can be the path to fragment shader file or the fragmentShader depending on readFromFile parameter
		* @param readFromFile: If true the shader class takes the vertexShader and fragmentShader as filePaths and reads it,
		*					   but it false shader class takes the vertexShader and fragmentShader as source code.
		*/
		Shader(const char* vertexShader, const char* fragmentShader, bool readFromFile = true);

		// Sets the shader uniform variblem name to value of float.
		void Uniform1f(const char* name, float value);
		// Sets the shader uniform variblem name to value of int.
		void Uniform1i(const char* name, int value);
		// Sets the shader uniform variblem name to value of vec2.
		void Uniform2v(const char* name, glm::vec2 value);
		// Sets the shader uniform variblem name to value of vec3.
		void Uniform3v(const char* name, glm::vec3 value);
		// Sets the shader uniform variblem name to value of vec4.
		void Uniform4v(const char* name, glm::vec4 value);
		// Sets the shader uniform variblem name to value of matrix 4 by 4.
		void Uniform4x4mat(const char* name, glm::mat4x4 value);

		// Bind this shader program
		void bind();

		// Returns the ID of this shader program
		GLuint getShaderID();
	private:
		GLuint loadShader(const char* file, int type, bool readFromFile);
		GLuint m_ID;
	};
}
