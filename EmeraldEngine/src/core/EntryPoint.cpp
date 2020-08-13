#include "emeraldengine_pch.h"
#include "core/EntryPoint.h"

//--- External vendor libraries ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// --- Interface includes ---
#include "core/Application.h"

//--- Debugging utils ---
#include "core/debug/InternalLog.h"


int main() {
	EE_CORE_LOG_INFO("Starting EmeraldEngine");

	//initialize GLFW
	if (!glfwInit()) {
		EE_CORE_LOG_CRITICAL("Failed to initialize GLFW");
		return -1;
	}

	//create GLFW window
	EmeraldEngine::WindowProperties& windowProperties = EmeraldEngine::getPropertyMemory();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(windowProperties.width, windowProperties.height, windowProperties.title, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//load openGL using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		EE_CORE_LOG_CRITICAL("Failed to load openGL with GLAD");
		return -1;
	}

	glViewport(0, 0, windowProperties.width, windowProperties.height);


	//get application
	EmeraldEngine::Application* application = EmeraldEngine::createApplication();
	application->initialize();


	//terminate program
	application->terminate();
	delete application;

	glfwTerminate();

	return 0;
}

//--- User-defined application to run on the emerald engine ---
extern EmeraldEngine::Application* EmeraldEngine::createApplication();
extern EmeraldEngine::WindowProperties& EmeraldEngine::getPropertyMemory();
