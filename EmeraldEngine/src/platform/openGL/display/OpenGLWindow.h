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
		std::shared_ptr<WindowProperties> windowProperties;

		GLuint quadVaoId;
		GLuint quadVboId;

	public:
		OpenGLWindow(std::shared_ptr<WindowProperties>& windowProperties);
		~OpenGLWindow();

		void renderQuad() const override;
		void setBackgroundColor(float red, float green, float blue) const override;

		void resetTime() override;
		double getTime() const override;

		void preUpdate() override;
		void postUpdate() override;

		bool isKeyPressed(Key keyCode) const override;
		bool isMouseButtonPressed(MouseButton mouseButtonCode) const override;
		MousePosition getMousePosition() const override;
	};
}
