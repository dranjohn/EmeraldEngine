#pragma once

//--- Standard library ---
#include <forward_list>
#include <memory>

//--- Interface files ---
#include "core/resourceManagement/ResourceManager.h"

//--- Internal files ---
#include "core/resourceManagement/shader/InternalShader.h"
#include "core/resourceManagement/texture/InternalTexture.h"


namespace EmeraldEngine {
	class InternalResourceManager : public ResourceManager {
	private:
		std::forward_list<std::shared_ptr<InternalShader>> shaders;
		std::forward_list<std::shared_ptr<InternalTexture>> textures;

	public:
		std::weak_ptr<Shader> createShader(const ShaderSource& source, bool fromFile) override;
		void cleanupShaders() override;

		std::weak_ptr<Texture> loadTexture(std::string textureFile, TextureFilter filter) override;
		void cleanupTextures() override;
	};
}
