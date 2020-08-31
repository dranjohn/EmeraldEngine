#pragma once

//--- Standard library ---
#include <memory>
#include <string>

//--- Interface files ---
#include "core/resourceManagement/shader/Shader.h"
#include "core/resourceManagement/shader/ShaderSource.h"
#include "core/resourceManagement/texture/Texture.h"
#include "core/resourceManagement/texture/TextureOptions.h"


namespace EmeraldEngine {
	class ResourceManager { //TODO: go off weak pointers
	public:
		virtual std::weak_ptr<Shader> createShader(const ShaderSource& source, bool fromFile) = 0;
		virtual void cleanupShaders() = 0;

		virtual std::weak_ptr<Texture> loadTexture(std::string textureFile, TextureFilter filter) = 0;
		virtual void cleanupTextures() = 0;

		inline void cleanup() {
			cleanupShaders();
			cleanupTextures();
		}
	};
}
