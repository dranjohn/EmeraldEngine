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

	public:
		OpenGLWindow(std::shared_ptr<WindowProperties>& windowProperties);
		~OpenGLWindow();

		void renderQuad() override;

		void resetTime() override;
		double getTime() override;

		void preUpdate() override;
		void postUpdate() override;
	};
}
