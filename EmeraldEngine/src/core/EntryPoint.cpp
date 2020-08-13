#include "emeraldengine_pch.h"
#include "core/EntryPoint.h"

//--- External vendor libraries ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 360;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "EmeraldEngine", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//load openGL using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		EE_CORE_LOG_CRITICAL("Failed to load openGL with GLAD");
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	glfwTerminate();
	return 0;
}
