#include "emeraldengine_pch.h"
#include "core/EntryPoint.h"

//--- Interface files ---
#include "core/Application.h"

//--- Internal files ---
#include "core/display/InternalWindow.h"
#include "platform/openGL/display/OpenGLWindow.h"

//--- Debugging utils ---
#include "core/debug/InternalLog.h"


int main() {
	EE_CORE_LOG_INFO("Starting EmeraldEngine");

	//create openGL window
	std::shared_ptr<EmeraldEngine::WindowProperties> windowProperties = EmeraldEngine::getPropertyMemory();
	EmeraldEngine::InternalWindow* window = new EmeraldEngine::OpenGLWindow(windowProperties);


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
