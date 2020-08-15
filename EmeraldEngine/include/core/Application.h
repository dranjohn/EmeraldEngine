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
}
