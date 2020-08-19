#pragma once

//--- Standard library ---
#include <string>


namespace EmeraldEngine {
	class Shader {
	protected:
		Shader() = default;

	public:
		virtual void use() = 0;

		virtual void loadBool(std::string location, bool value) = 0;
		virtual void loadFloat(std::string location, float value) = 0;

		virtual void loadFloatv2(std::string location, float x, float y) = 0;
		virtual void loadFloatv3(std::string location, float x, float y, float z) = 0;
		virtual void loadFloatv4(std::string location, float x, float y, float z, float w) = 0;

		virtual void loadMatrixv4x4(std::string location, float value[16]) = 0;
	};
}
