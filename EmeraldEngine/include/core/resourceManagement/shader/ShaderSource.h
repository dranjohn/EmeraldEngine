#pragma once

//--- Standard library ---
#include <String>
#include <unordered_map>


namespace EmeraldEngine {
	enum class ShaderType {
		vertex_shader,
		tesselation_control,
		tesselation_evaluation,
		geometry_shader,
		fragment_shader
	};


	typedef std::unordered_map<ShaderType, std::string> ShaderSource;
}
