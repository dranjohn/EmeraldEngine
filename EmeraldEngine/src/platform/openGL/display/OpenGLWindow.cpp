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

	void frambufferSizeCallback(GLFWwindow* window, int width, int height);


	OpenGLWindow::OpenGLWindow(const WindowProperties& initialWindowProperties) :
		InternalWindow(initialWindowProperties)
	{
		//initialize GLFW
		if (!glfwInit()) {
			EE_CORE_LOG_CRITICAL("Failed to initialize GLFW");
			//TODO: throw exception
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, initialWindowProperties.resizable);

		window = glfwCreateWindow(initialWindowProperties.width, initialWindowProperties.height, initialWindowProperties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		//load openGL using GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			EE_CORE_LOG_CRITICAL("Failed to load openGL with GLAD");
			//TODO: throw exception
		}

		glViewport(0, 0, initialWindowProperties.width, initialWindowProperties.height);
		glfwSetFramebufferSizeCallback(window, frambufferSizeCallback);


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

	double OpenGLWindow::getTime() const {
		return glfwGetTime();
	}


	void OpenGLWindow::preUpdate() {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLWindow::postUpdate() {
		glfwSwapBuffers(window);
	}


	bool OpenGLWindow::continueRunning() {
		return !glfwWindowShouldClose(window);
	}


	bool OpenGLWindow::isKeyPressed(Key keyCode) const {
		return glfwGetKey(window, keyCode) == GLFW_PRESS;
	}

	bool OpenGLWindow::isMouseButtonPressed(MouseButton mouseButtonCode) const {
		return glfwGetMouseButton(window, mouseButtonCode) == GLFW_PRESS;
	}

	MousePosition OpenGLWindow::getMousePosition() const {
		MousePosition position;
		glfwGetCursorPos(window, &position.x, &position.y);

		return position;
	}


	void frambufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}
