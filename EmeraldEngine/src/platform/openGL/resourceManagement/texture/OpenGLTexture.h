#pragma once

//--- Standard library ---
#include <string>

//--- External vendor libraries ---
#include <glad/glad.h>

//--- Interface files ---
#include "core/resourceManagement/texture/Texture.h"
#include "core/resourceManagement/texture/TextureOptions.h"


namespace EmeraldEngine {
	class OpenGLTexture : public Texture {
	private:
		GLuint textureId;

	public:
		OpenGLTexture(GLsizei width, GLsizei height, const GLvoid* data, TextureFilter filter);
		~OpenGLTexture();

		void use(unsigned int slot) override;
	};
}
