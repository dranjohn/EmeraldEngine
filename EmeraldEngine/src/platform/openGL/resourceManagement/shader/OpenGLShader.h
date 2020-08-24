#pragma once

//--- Standard library ---
#include <string>

//--- External vendor libraries ---
#include <glad/glad.h>

//--- Interface files ---
#include "core/resourceManagement/shader/Shader.h"


namespace EmeraldEngine {
	class OpenGLShader : public Shader {
	private:
		GLuint programId = glCreateProgram();

	public:
		OpenGLShader(std::string vertexShaderSource, std::string fragmentShaderSource);
		~OpenGLShader();

		void use() override;

		void loadBool(std::string location, bool value) override;
		void loadFloat(std::string location, float value) override;

		void loadFloatv2(std::string location, float x, float y) override;
		void loadFloatv3(std::string location, float x, float y, float z) override;
		void loadFloatv4(std::string location, float x, float y, float z, float w) override;

		void loadMatrixv4x4(std::string location, float value[16]) override;

		void loadTexture(std::string location, unsigned int textureSlot) override;
	};
}
