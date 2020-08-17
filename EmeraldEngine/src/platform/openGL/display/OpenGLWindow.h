#pragma once

//--- External vendor libraries ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//--- Interface files ---
#include "core/Application.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"


namespace EmeraldEngine {
	class OpenGLWindow : public InternalWindow {
	private:
		GLFWwindow* window;

		GLuint quadVaoId;
		GLuint quadVboId;

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
		MousePosition getMousePosition() const override;
	};
}
