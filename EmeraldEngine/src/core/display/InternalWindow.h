#pragma once

//--- External vendor libraries ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//--- Interface files ---
#include "core/Application.h"
#include "core/display/Window.h"
#include "core/display/WindowProperties.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "core/resourceManagement/shader/InternalShader.h"
#include "core/resourceManagement/texture/InternalTexture.h"


namespace EmeraldEngine {
	class InternalWindow : public Window {
	private:
		// -----------------
		// Window properties
		// -----------------
		WindowData windowData;

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
		InternalWindow(const WindowProperties& initialWindowProperties);
		~InternalWindow();


		inline WindowProperties getWindowProperties() const override { return windowData.windowProperties; }
		inline WindowEventCallbacks& getEventCallbacks() override { return windowData.windowEventCallbacks; }


		void renderQuad() const override;
		void renderQuads(unsigned int amount) const override;

		void setBackgroundColor(float red, float green, float blue) override;
		void useFilter(std::weak_ptr<Shader> filter) override;
		void clearFilter() override;


		void resetTime();
		double getTime() const;

		void preUpdate();
		void postUpdate();

		bool continueRunning();


		bool isKeyPressed(Key keyCode) const override;
		bool isMouseButtonPressed(MouseButton mouseButtonCode) const override;
		CursorPosition getCursorPosition() const override;


		void resize(unsigned int width, unsigned int height) override;
		void setTitle(std::string title) override;

		void close() override;
	};
}
