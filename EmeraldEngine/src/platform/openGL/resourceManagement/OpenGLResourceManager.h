#pragma once

//--- Standard library ---
#include <forward_list>

//--- Interface files ---
#include "core/resourceManagement/ResourceManager.h"

//--- Internal files ---
#include "platform/openGL/resourceManagement/shader/OpenGLShader.h"
#include "platform/openGL/resourceManagement/texture/OpenGLTexture.h"


namespace EmeraldEngine {
	class OpenGLResourceManager : public ResourceManager {
	private:
		std::forward_list<std::shared_ptr<OpenGLShader>> shaders;
		std::forward_list<std::shared_ptr<OpenGLTexture>> textures;

	public:
		std::weak_ptr<Shader> createShader(const ShaderSource& source, bool fromFile) override;
		void cleanupShaders() override;

		std::weak_ptr<Texture> loadTexture(std::string textureFile, TextureFilter filter) override;
		void cleanupTextures() override;
	};
}
