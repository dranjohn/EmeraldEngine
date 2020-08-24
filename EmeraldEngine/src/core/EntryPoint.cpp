#include "emeraldengine_pch.h"
#include "core/EntryPoint.h"

//--- Interface files ---
#include "core/Application.h"
#include "core/display/Window.h"
#include "platform/Platform.h"
#include "core/utility/NonAssignable.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "platform/openGL/display/OpenGLWindow.h"
#include "platform/openGL/resourceManagement/OpenGLResourceManager.h"

//--- Debugging utils ---
#include "debug/InternalLog.h"


int main() {
	EE_CORE_LOG_INFO("Starting EmeraldEngine");

	//request the platform the user wants to use
	EmeraldEngine::Platform platform = EmeraldEngine::getPlatform();

	//create openGL window
	EmeraldEngine::WindowProperties windowProperties = EmeraldEngine::getInitialWindowProperties();
	EmeraldEngine::InternalWindow* window;
	EmeraldEngine::ResourceManager* resourceManager;

	switch (platform) {
		case EmeraldEngine::Platform::defaultPlatform: //currently, the default platform is openGL
		case EmeraldEngine::Platform::opengl:
			window = new EmeraldEngine::OpenGLWindow(windowProperties);
			resourceManager = new EmeraldEngine::OpenGLResourceManager();
			break;
		default:
			EE_CORE_LOG_WARN("Got unknown platform, treating it as missing platform");
		case EmeraldEngine::Platform::missingPlatform:
			EE_CORE_LOG_CRITICAL("Missing platform, shutting down EmeraldEngine");
			return 0;
	}


	//get application
	EmeraldEngine::Application* application = EmeraldEngine::createApplication(
		EmeraldEngine::NonAssignable<EmeraldEngine::Window>(window),
		EmeraldEngine::NonAssignable<EmeraldEngine::ResourceManager>(resourceManager)
	);


	//run main loop
	double deltaTime;
	window->resetTime();

	while (window->continueRunning()) {
		window->preUpdate();

		deltaTime = window->getTime();
		window->resetTime();
		application->update(deltaTime);

		window->postUpdate();
	}


	//terminate program
	delete application;

	resourceManager->cleanup();
	delete resourceManager;
	delete window;

	return 0;
}

//--- User-defined application to run on the emerald engine ---
extern EmeraldEngine::Application* EmeraldEngine::createApplication(EmeraldEngine::NonAssignable<EmeraldEngine::Window> gameWindow, EmeraldEngine::NonAssignable<EmeraldEngine::ResourceManager> resourceManager);
extern EmeraldEngine::WindowProperties EmeraldEngine::getInitialWindowProperties();
extern EmeraldEngine::Platform EmeraldEngine::getPlatform();
