#pragma once

//--- Standard library ---
#include <cstdint>
#include <memory>
#include <string>


namespace EmeraldEngine {
	class Application {
	public:
		virtual void initialize() = 0;
		virtual void terminate() = 0;

		virtual void update(double deltaTime) = 0;
	};

	Application* createApplication();


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
