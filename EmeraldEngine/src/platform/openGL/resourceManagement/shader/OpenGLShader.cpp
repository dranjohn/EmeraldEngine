#include "emeraldengine_pch.h"
#include "OpenGLShader.h"

//--- Standard library ---
#include <cstdint>

//--- Debug utils ---
#include "debug/InternalLog.h"


namespace EmeraldEngine {
	GLenum getShaderTypeEnumValue(ShaderType type) {
		switch (type) {
		case ShaderType::vertex_shader:
			return GL_VERTEX_SHADER;
		case ShaderType::tesselation_control:
			return GL_TESS_CONTROL_SHADER;
		case ShaderType::tesselation_evaluation:
			return GL_TESS_EVALUATION_SHADER;
		case ShaderType::geometry_shader:
			return GL_GEOMETRY_SHADER;
		case ShaderType::fragment_shader:
			return GL_FRAGMENT_SHADER;

		default:
			//TODO: throw exception
			return 0;
		}
	}


	GLuint createShader(std::string source, GLenum type) {
		GLuint shaderId = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();

		glShaderSource(shaderId, 1, &sourceCStr, NULL);
		glCompileShader(shaderId);

		return shaderId;
	}

	OpenGLShader::OpenGLShader(const ShaderSource& source) {
		if (source.find(ShaderType::vertex_shader) == source.end() || source.find(ShaderType::fragment_shader) == source.end()) {
			EE_CORE_LOG_ERROR("OpenGL shaders require at least a vertex and fragment shader");
			//TODO: throw exception
		}

		GLuint* shaders = new GLuint[source.size()];
		size_t pointer = 0;

		for (auto shaderSource : source) {
			shaders[pointer] = createShader(shaderSource.second, getShaderTypeEnumValue(shaderSource.first));
			glAttachShader(programId, shaders[pointer]);

			++pointer;
		}

		glLinkProgram(programId);

		for (size_t i = 0; i < pointer; ++i) {
			glDeleteShader(shaders[i]);
		}
		delete[] shaders;
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


	void OpenGLShader::loadTexture(std::string location, unsigned int textureSlot) {
		glUniform1i(glGetUniformLocation(programId, location.c_str()), (GLint)textureSlot);
	}
}
