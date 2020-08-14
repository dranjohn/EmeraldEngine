#pragma once

//--- Standard library ---
#include <cstdint>
#include <memory>
#include <string>

//--- Interface files ---
#include "core/display/Window.h"


namespace EmeraldEngine {
	class Application {
	public:
		virtual void update(double deltaTime) = 0;
	};

	Application* createApplication(const EmeraldEngine::Window& gameWindow);


	struct WindowProperties {
		unsigned int width;
		unsigned int height;

		std::string title;

		bool continueRunning;

		WindowProperties(unsigned int width, unsigned int height, std::string title, bool continueRunning) :
			width(width),
			height(height),
			title(title),
			continueRunning(continueRunning)
		{}
	};

	std::shared_ptr<WindowProperties> getPropertyMemory();
}
