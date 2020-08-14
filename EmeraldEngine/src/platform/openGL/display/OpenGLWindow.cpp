#include "emeraldengine_pch.h"
#include "OpenGLWindow.h"

//--- Debugging utils ---
#include "core/debug/InternalLog.h"


namespace EmeraldEngine {
	OpenGLWindow::OpenGLWindow(std::shared_ptr<WindowProperties>& windowProperties) : windowProperties(windowProperties) {
		//initialize GLFW
		if (!glfwInit()) {
			EE_CORE_LOG_CRITICAL("Failed to initialize GLFW");
			//TODO: throw exception
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, false);

		window = glfwCreateWindow(windowProperties->width, windowProperties->height, (windowProperties->title).c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		//load openGL using GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			EE_CORE_LOG_CRITICAL("Failed to load openGL with GLAD");
			//TODO: throw exception
		}

		glViewport(0, 0, windowProperties->width, windowProperties->height);
	}

	OpenGLWindow::~OpenGLWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}


	void OpenGLWindow::renderQuad() {

	}


	void OpenGLWindow::resetTime() {
		glfwSetTime(0.0);
	}

	double OpenGLWindow::getTime() {
		return glfwGetTime();
	}


	void OpenGLWindow::preUpdate() {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLWindow::postUpdate() {
		glfwSwapBuffers(window);
		windowProperties->continueRunning &= !glfwWindowShouldClose(window);
	}
}
