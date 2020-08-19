#include "emeraldengine_pch.h"
#include "OpenGLShader.h"


namespace EmeraldEngine {
	GLuint createShader(std::string source, GLenum type) {
		GLuint shaderId = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();

		glShaderSource(shaderId, 1, &sourceCStr, NULL);
		glCompileShader(shaderId);

		return shaderId;
	}

	OpenGLShader::OpenGLShader(std::string vertexShaderSource, std::string fragmentShaderSource) {
		GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
		GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);

		glLinkProgram(programId);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(programId);
	}


	void OpenGLShader::use() {
		glUseProgram(programId);
	}


	void OpenGLShader::loadBool(std::string location, bool value) {
		glUniform1f(glGetUniformLocation(programId, location.c_str()), value ? 1.0f : 0.0f);
	}

	void OpenGLShader::loadFloat(std::string location, float value) {
		glUniform1f(glGetUniformLocation(programId, location.c_str()), value);
	}

	void OpenGLShader::loadFloatv2(std::string location, float x, float y) {
		glUniform2f(glGetUniformLocation(programId, location.c_str()), x, y);
	}

	void OpenGLShader::loadFloatv3(std::string location, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(programId, location.c_str()), x, y, z);
	}

	void OpenGLShader::loadFloatv4(std::string location, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(programId, location.c_str()), x, y, z, w);
	}


	void OpenGLShader::loadMatrixv4x4(std::string location, float value[16]) {
		glUniformMatrix4fv(glGetUniformLocation(programId, location.c_str()), 1, false, value);
	}
}
