#include "Shader.h"

namespace LampEngine {
	Shader::Shader(const char* vertexShader, const char* fragmentShader, bool readFromFile) {
		GLuint vertexID = loadShader(vertexShader, GL_VERTEX_SHADER, readFromFile);
		GLuint fragmentID = loadShader(fragmentShader, GL_FRAGMENT_SHADER, readFromFile);

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexID);
		glAttachShader(m_ID, fragmentID);
		glLinkProgram(m_ID);
		glValidateProgram(m_ID);
		LOGdebug("A Shader Program Has Been Compiled.");
		bind();
	}
	void Shader::Uniform1f(const char* name, float value) {
		glUniform1f(glGetUniformLocation(m_ID, name), value);
	}
	void Shader::Uniform1i(const char* name, int value) {
		glUniform1i(glGetUniformLocation(m_ID, name), value);
	}
	void Shader::Uniform2v(const char* name, glm::vec2 value) {
		glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
	}
	void Shader::Uniform3v(const char* name, glm::vec3 value) {
		glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
	}
	void Shader::Uniform4v(const char* name, glm::vec4 value) {
		glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
	}
	void Shader::Uniform4x4mat(const char* name, glm::mat4x4 value) {
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::bind() {
		glUseProgram(m_ID);
	}
	GLuint Shader::getShaderID() {
		return m_ID;
	}
	GLuint Shader::loadShader(const char* shader, int type, bool readFromFile) {
		std::string shaderSrc;
		if (readFromFile) shaderSrc = FileUtils::ReadTextFile(shader);
		else shaderSrc = shader;

		const char* shaderCode = shaderSrc.c_str();
		GLint hasCompiled;
		GLuint shaderID = glCreateShader(type);

		glShaderSource(shaderID, 1, &shaderCode, NULL);
		glCompileShader(shaderID);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {
			std::string shaderType;
			switch (type) {
			case GL_VERTEX_SHADER:
				shaderType = "Vertex";
				break;
			case GL_FRAGMENT_SHADER:
				shaderType = "Fragment";
				break;
			};

			char infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			LOGerror("{0} Shader Has Failed To Compile:\n                   {1}", shaderType, infoLog);
		}
		return shaderID;
	}
}