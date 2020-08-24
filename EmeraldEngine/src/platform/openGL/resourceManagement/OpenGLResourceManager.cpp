#include "emeraldengine_pch.h"
#include "OpenGLResourceManager.h"

//--- External vendor libraries ---
#include <glad/glad.h>

//--- Debugging utils ---
#include "debug/InternalLog.h"


namespace EmeraldEngine {
	std::string readFile(std::string fileName) {
		std::fstream fileContentStream(fileName);
		std::ostringstream fileContents;

		fileContents << fileContentStream.rdbuf();
		fileContentStream.close();

		return fileContents.str();
	}


	std::weak_ptr<Shader> OpenGLResourceManager::createShader(const ShaderSource& source, bool fromFile) {
		std::shared_ptr<OpenGLShader> shader = nullptr;

		if (fromFile) {
			ShaderSource fileSource;

			for (auto shaderSourceFile : source) {
				fileSource.emplace(shaderSourceFile.first, readFile(shaderSourceFile.second));
			}

			shader = std::make_shared<OpenGLShader>(fileSource);
		}
		else {
			shader = std::make_shared<OpenGLShader>(source);
		}

		shaders.push_front(shader);
		return shader;
	}

	void OpenGLResourceManager::cleanupShaders() {
		shaders.clear();
	}

	
	std::weak_ptr<Texture> OpenGLResourceManager::loadTexture(std::string textureFile, TextureFilter filter) {
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		GLvoid* data = (GLvoid*)stbi_load(textureFile.c_str(), &width, &height, &nrChannels, 0);

		if (!data) {
			EE_CORE_LOG_ERROR("Failed to load texture {}", textureFile);
			//TODO: throw exception
		}

		if ((width & (width - 1)) != 0 || (height & (height - 1)) != 0) {
			EE_CORE_LOG_ERROR("Can't use texture {} with dimensions {}x{}", textureFile, width, height);
			//TODO: throw exception
		}

		std::shared_ptr<OpenGLTexture> texture = std::make_shared<OpenGLTexture>(width, height, data, filter);
		textures.push_front(texture);

		stbi_image_free(data);

		return texture;
	}

	void OpenGLResourceManager::cleanupTextures() {
		textures.clear();
	}
}
