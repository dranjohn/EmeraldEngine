#pragma once

//--- Standard library ---
#include <string>

//--- External vendor libraries ---
#include <glad/glad.h>

//--- Interface files ---
#include "core/resourceManagement/texture/Texture.h"
#include "core/resourceManagement/texture/TextureOptions.h"


namespace EmeraldEngine {
	class InternalTexture : public Texture {
	private:
		GLuint textureId;

	public:
		InternalTexture(GLsizei width, GLsizei height, const GLvoid* data, TextureFilter filter);
		~InternalTexture();

		void use(unsigned int slot) override;
	};
}
