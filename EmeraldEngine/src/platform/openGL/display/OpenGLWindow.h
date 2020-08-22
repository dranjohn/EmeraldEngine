#pragma once

//--- External vendor libraries ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//--- Standard library ---
#include <forward_list>

//--- Interface files ---
#include "core/Application.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "platform/openGL/display/shader/OpenGLShader.h"
#include "platform/openGL/display/texture/OpenGLTexture.h"


namespace EmeraldEngine {
	class OpenGLWindow : public InternalWindow {
	private:
		GLFWwindow* window;

		GLuint quadVaoId;
		GLuint quadVboId;

		std::forward_list<std::shared_ptr<OpenGLShader>> shaders;
		std::forward_list<std::shared_ptr<OpenGLTexture>> textures;

	public:
		OpenGLWindow(const WindowProperties& initialWindowProperties);
		~OpenGLWindow();

		void renderQuad() const override;
		void setBackgroundColor(float red, float green, float blue) const override;

		void resetTime() override;
		double getTime() const override;

		void preUpdate() override;
		void postUpdate() override;

		bool continueRunning() override;

		bool isKeyPressed(Key keyCode) const override;
		bool isMouseButtonPressed(MouseButton mouseButtonCode) const override;
		CursorPosition getCursorPosition() const override;


		void resize(unsigned int width, unsigned int height) override;
		void setTitle(std::string title) override;

		void close() override;


		std::weak_ptr<Shader> createShader(std::string sourceDirectory) override;
		void cleanupShaders() override;

		std::weak_ptr<Texture> loadTexture(std::string textureFile, TextureFilter filter) override;
		void cleanupTextures() override;
	};
}
