#pragma once

//--- External vendor libraries ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//--- Interface files ---
#include "core/Application.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "platform/openGL/resourceManagement/shader/OpenGLShader.h"
#include "platform/openGL/resourceManagement/texture/OpenGLTexture.h"


namespace EmeraldEngine {
	class OpenGLWindow : public InternalWindow {
	private:
		// -----------------
		// Window properties
		// -----------------
		GLFWwindow* window;

		GLuint quadVaoId;
		GLuint quadVboId;

		// --------------
		// Post-processor
		// --------------
		bool postProcessorUsed = false;

		GLuint screenVaoId;
		GLuint screenVboId;
		
		GLuint multisampledFrameBuffer = 0;
		GLuint multisampledRenderBuffer = 0;

		GLuint frameBuffer = 0;
		GLuint frameBufferTexture = 0;

		std::weak_ptr<Shader> postProcessingShader;

	public:
		OpenGLWindow(const WindowProperties& initialWindowProperties);
		~OpenGLWindow();

		void renderQuad() const override;
		void renderQuads(unsigned int amount) const override;

		void setBackgroundColor(float red, float green, float blue) override;
		void useFilter(std::weak_ptr<Shader> filter) override;
		void clearFilter() override;

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
	};
}
