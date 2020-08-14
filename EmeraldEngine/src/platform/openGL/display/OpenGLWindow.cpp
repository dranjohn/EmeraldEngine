#include "emeraldengine_pch.h"
#include "OpenGLWindow.h"

//--- Debugging utils ---
#include "core/debug/InternalLog.h"


namespace EmeraldEngine {
	static const float quadVertices[8] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};


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


		//load Quad
		glGenVertexArrays(1, &quadVaoId);
		glBindVertexArray(quadVaoId);

		glGenBuffers(1, &quadVboId);
		glBindBuffer(GL_ARRAY_BUFFER, quadVboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	OpenGLWindow::~OpenGLWindow() {
		glDisableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &quadVboId);
		glDeleteVertexArrays(1, &quadVaoId);

		glfwDestroyWindow(window);
		glfwTerminate();
	}


	void OpenGLWindow::renderQuad() const {
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	void OpenGLWindow::setBackgroundColor(float red, float green, float blue) const {
		glClearColor(red, green, blue, 1.0f);
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
