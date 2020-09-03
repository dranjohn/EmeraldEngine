#include "emeraldengine_pch.h"
#include "core/EntryPoint.h"

//--- Interface files ---
#include "core/Application.h"
#include "core/display/Window.h"
#include "core/utility/NonAssignable.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "core/resourceManagement/InternalResourceManager.h"

//--- Debugging utils ---
#include "debug/InternalLog.h"


int main() {
	EE_CORE_LOG_INFO("Starting EmeraldEngine");

	//create openGL window
	EmeraldEngine::WindowProperties windowProperties = EmeraldEngine::getInitialWindowProperties();
	EmeraldEngine::InternalWindow* window = new EmeraldEngine::InternalWindow(windowProperties);
	EmeraldEngine::ResourceManager* resourceManager = new EmeraldEngine::InternalResourceManager();

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
extern EmeraldEngine::Application* EmeraldEngine::createApplication(
	EmeraldEngine::NonAssignable<EmeraldEngine::Window> gameWindow,
	EmeraldEngine::NonAssignable<EmeraldEngine::ResourceManager> resourceManager
);
extern EmeraldEngine::WindowProperties EmeraldEngine::getInitialWindowProperties();
