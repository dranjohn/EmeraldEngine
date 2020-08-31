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

	static const float screenVertices[8] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f
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

		//create window
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


		//enable openGL error handling
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback([](
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
		{
			switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				EE_CORE_LOG_INFO("OpenGL notification: {}", message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
			case GL_DEBUG_SEVERITY_MEDIUM:
				EE_CORE_LOG_WARN("OpenGL warning: {}", message);
				break;
			default:
			case GL_DEBUG_SEVERITY_HIGH:
				EE_CORE_LOG_ERROR("OpenGL error: {}", message);
				break;
			}
		}, 0);


		//load render quad
		glGenVertexArrays(1, &quadVaoId);
		glBindVertexArray(quadVaoId);

		glGenBuffers(1, &quadVboId);
		glBindBuffer(GL_ARRAY_BUFFER, quadVboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		//load screen quad
		glGenVertexArrays(1, &screenVaoId);
		glBindVertexArray(screenVaoId);

		glGenBuffers(1, &screenVboId);
		glBindBuffer(GL_ARRAY_BUFFER, screenVboId);

		glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		//create post-processor
		//create multisampled buffer
		glGenFramebuffers(1, &multisampledFrameBuffer);
		glGenRenderbuffers(1, &multisampledRenderBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, multisampledFrameBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, multisampledRenderBuffer);

		//TODO: change post-processing framebuffer resolution
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, 1280, 720);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, multisampledRenderBuffer);

		//check if the multi-sampled framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			EE_CORE_LOG_ERROR("Failed to create a multisampled framebuffer for post-processing");
		}

		//create texture to render to
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

		glGenTextures(1, &frameBufferTexture);
		glBindTexture(GL_TEXTURE_2D, frameBufferTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//attach the texture to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture, 0);

		//check if the framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			EE_CORE_LOG_ERROR("Failed to create a framebuffer for post-processing");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//restore default quad
		glBindVertexArray(quadVaoId);
		glBindBuffer(GL_ARRAY_BUFFER, quadVboId);
	}

	OpenGLWindow::~OpenGLWindow() {
		//cleanup renderable quad
		glDisableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &quadVboId);
		glDeleteVertexArrays(1, &quadVaoId);

		glDeleteBuffers(1, &screenVboId);
		glDeleteVertexArrays(1, &screenVaoId);

		glDeleteFramebuffers(1, &multisampledFrameBuffer);
		glDeleteRenderbuffers(1, &multisampledRenderBuffer);

		glDeleteFramebuffers(1, &frameBuffer);


		//terminate window and GLFW
		glfwDestroyWindow(window);
		glfwTerminate();
	}


	void OpenGLWindow::renderQuad() const {
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	void OpenGLWindow::renderQuads(unsigned int amount) const {
		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, amount);
	}


	void OpenGLWindow::setBackgroundColor(float red, float green, float blue) {
		glClearColor(red, green, blue, 1.0f);
	}

	void OpenGLWindow::useFilter(std::weak_ptr<Shader> filter) {
		postProcessorUsed = true;
		postProcessingShader = filter;
	}

	void OpenGLWindow::clearFilter() {
		postProcessorUsed = false;

		//bind the default quad and framebuffer upon disabling the post-processor
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, windowData.windowProperties.dimensions.width, windowData.windowProperties.dimensions.height);

		glBindVertexArray(quadVaoId);
		glBindBuffer(GL_ARRAY_BUFFER, quadVboId);
	}


	void OpenGLWindow::resetTime() {
		glfwSetTime(0.0);
	}

	double OpenGLWindow::getTime() const {
		return glfwGetTime();
	}


	void OpenGLWindow::preUpdate() {
		if (postProcessorUsed) {
			//bind the intermediary buffer
			glBindFramebuffer(GL_FRAMEBUFFER, multisampledFrameBuffer);
			glViewport(0, 0, 1280, 720);

			//bind the default quad
			glBindVertexArray(quadVaoId);
			glBindBuffer(GL_ARRAY_BUFFER, quadVboId);
			
		}
		glClear(GL_COLOR_BUFFER_BIT);

		//polls events up until now
		glfwPollEvents();
	}

	void OpenGLWindow::postUpdate() {
		if (postProcessorUsed) {
			//blit from multisampled framebuffer to texture
			glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampledFrameBuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);

			glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_NEAREST);

			//switch to the default window framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, windowData.windowProperties.dimensions.width, windowData.windowProperties.dimensions.height);

			//render texture to screen
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frameBufferTexture);

			postProcessingShader.lock()->use();
			postProcessingShader.lock()->loadTexture("frame", 0);

			glBindVertexArray(screenVaoId);
			glBindBuffer(GL_ARRAY_BUFFER, screenVboId);

			renderQuad();
		}

		//display newly rendered frame
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
