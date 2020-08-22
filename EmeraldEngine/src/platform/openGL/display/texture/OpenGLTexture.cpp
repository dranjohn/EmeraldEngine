#include "emeraldengine_pch.h"
#include "OpenGLTexture.h"

//--- Debugging utils ---
#include "core/debug/InternalLog.h"


namespace EmeraldEngine {
	OpenGLTexture::OpenGLTexture(GLsizei width, GLsizei height, const GLvoid* data, TextureFilter filter) {
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		//TODO: fix color mode
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		GLint textureFilter;

		switch (filter) {
		default:
			EE_CORE_LOG_WARN("Unknown texture filter, defaulting to linear filtering instead");
		case TextureFilter::linear:
			textureFilter = GL_LINEAR;
			break;
		case TextureFilter::nearest:
			textureFilter = GL_NEAREST;
			break;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilter);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &textureId);
	}


	void OpenGLTexture::use(unsigned int slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
}
