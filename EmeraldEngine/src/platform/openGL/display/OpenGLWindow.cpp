#include "emeraldengine_pch.h"
#include "OpenGLWindow.h"

//--- External vendor libraries ---
#include "stb_image.h"

//--- Interface files ---
#include "core/input/InputData.h"
#include "core/input/KeyCode.h"

//--- Debugging utils ---
#include "debug/InternalLog.h"


namespace EmeraldEngine {
	static const float quadVertices[8] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};


	void frambufferSizeCallback(GLFWwindow* window, int width, int height);


	void windowResizeEvent(GLFWwindow* window, int width, int height);

	void windowIconifyEvent(GLFWwindow* window, int iconified);
	void windowMaximizeEvent(GLFWwindow* window, int maximized);
	void windowFocusEvent(GLFWwindow* window, int focused);

	void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void windowCursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
	void windowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


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

		window = glfwCreateWindow(initialWindowProperties.dimensions.width, initialWindowProperties.dimensions.height, initialWindowProperties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		//load openGL using GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			EE_CORE_LOG_CRITICAL("Failed to load openGL with GLAD");
			//TODO: throw exception
		}

		glViewport(0, 0, initialWindowProperties.dimensions.width, initialWindowProperties.dimensions.height);
		glfwSetFramebufferSizeCallback(window, frambufferSizeCallback);

		glfwSetWindowUserPointer(window, &windowData);

		//add event callbacks
		if (initialWindowProperties.resizable) {
			glfwSetWindowSizeCallback(window, windowResizeEvent);
		}

		glfwSetWindowIconifyCallback(window, windowIconifyEvent);
		glfwSetWindowMaximizeCallback(window, windowMaximizeEvent);
		glfwSetWindowFocusCallback(window, windowFocusEvent);

		glfwSetKeyCallback(window, windowKeyCallback);

		glfwSetCursorPosCallback(window, windowCursorPositionCallback);
		glfwSetMouseButtonCallback(window, windowMouseButtonCallback);


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

	CursorPosition OpenGLWindow::getCursorPosition() const {
		CursorPosition position;
		glfwGetCursorPos(window, &position.x, &position.y);

		return position;
	}


	void OpenGLWindow::resize(unsigned int width, unsigned int height) {
		glfwSetWindowSize(window, width, height);
	}

	void OpenGLWindow::setTitle(std::string title) {
		glfwSetWindowTitle(window, title.c_str());
	}


	void OpenGLWindow::close() {
		glfwSetWindowShouldClose(window, true);
	}


	inline WindowData* getWindowData(GLFWwindow* window) {
		return (WindowData*)glfwGetWindowUserPointer(window);
	}


	void frambufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}


	void windowResizeEvent(GLFWwindow* window, int width, int height) {
		WindowData* windowData = getWindowData(window);

		windowData->windowProperties.dimensions = { (unsigned int)width, (unsigned int)height };
		std::invoke(windowData->windowEventCallbacks.resizeCallback, windowData->windowProperties.dimensions);
	}


	void windowIconifyEvent(GLFWwindow* window, int iconified) {
		WindowData* windowData = getWindowData(window);
		std::invoke(windowData->windowEventCallbacks.iconifyCallback, iconified == GL_TRUE);

	}

	void windowMaximizeEvent(GLFWwindow* window, int maximized) {
		WindowData* windowData = getWindowData(window);
		std::invoke(windowData->windowEventCallbacks.maximizeCallback, maximized == GL_TRUE);
	}

	void windowFocusEvent(GLFWwindow* window, int focused) {
		WindowData* windowData = getWindowData(window);
		std::invoke(windowData->windowEventCallbacks.focusCallback, focused == GL_TRUE);
	}


	void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData* windowData = getWindowData(window);
		std::invoke(windowData->windowEventCallbacks.keyCallback, (Key)key, (KeyAction)action);
	}


	void windowCursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
		WindowData* windowData = getWindowData(window);
		std::invoke(windowData->windowEventCallbacks.cursorPositionCallback, CursorPosition({ xPos, yPos }));
	}

	void windowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		WindowData* windowData = getWindowData(window);

		CursorPosition cursorPos;
		glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);

		std::invoke(windowData->windowEventCallbacks.mouseButtonCallback, MouseClick({ (MouseButton)button, (KeyAction)action }), cursorPos);
	}
}
