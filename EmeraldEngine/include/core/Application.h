#pragma once

//--- Standard library ---
#include <cstdint>


namespace EmeraldEngine {
	class Application {
	public:
		virtual void initialize() = 0;
		virtual void terminate() = 0;
	};

	Application* createApplication();


	struct WindowProperties {
		unsigned int width;
		unsigned int height;

		char* title;
	};

	WindowProperties& getPropertyMemory();
}
