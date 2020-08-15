#include "emeraldengine_pch.h"
#include "core/EntryPoint.h"

//--- Interface files ---
#include "core/Application.h"
#include "core/display/Window.h"
#include "platform/Platform.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "platform/openGL/display/OpenGLWindow.h"

//--- Debugging utils ---
#include "core/debug/InternalLog.h"


int main() {
	EE_CORE_LOG_INFO("Starting EmeraldEngine");

	//request the platform the user wants to use
	EmeraldEngine::Platform platform = EmeraldEngine::getPlatform();

	//create openGL window
	std::shared_ptr<EmeraldEngine::WindowProperties> windowProperties = EmeraldEngine::getPropertyMemory();
	EmeraldEngine::InternalWindow* window;

	switch (platform) {
		case EmeraldEngine::Platform::defaultPlatform: //currently, the default platform is openGL
		case EmeraldEngine::Platform::opengl:
			window = new EmeraldEngine::OpenGLWindow(windowProperties);
			break;
		default:
			EE_CORE_LOG_WARN("Got unknown platform, treating it as missing platform");
		case EmeraldEngine::Platform::missingPlatform:
			EE_CORE_LOG_CRITICAL("Missing platform, shutting down EmeraldEngine");
			return 0;
	}


	//get application
	EmeraldEngine::Application* application = EmeraldEngine::createApplication(*window);


	//run main loop
	double deltaTime;
	window->resetTime();

	while (windowProperties->continueRunning) {
		window->preUpdate();

		deltaTime = window->getTime();
		window->resetTime();
		application->update(deltaTime);

		window->postUpdate();
	}


	//terminate program
	delete application;
	delete window;

	return 0;
}

//--- User-defined application to run on the emerald engine ---
extern EmeraldEngine::Application* EmeraldEngine::createApplication(const EmeraldEngine::Window& gameWindow);
extern std::shared_ptr<EmeraldEngine::WindowProperties> EmeraldEngine::getPropertyMemory();
extern EmeraldEngine::Platform EmeraldEngine::getPlatform();
