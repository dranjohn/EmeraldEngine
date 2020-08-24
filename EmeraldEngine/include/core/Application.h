#pragma once

//--- Standard library ---
#include <cstdint>
#include <memory>
#include <string>

//--- Interface files ---
#include "core/display/Window.h"
#include "core/resourceManagement/ResourceManager.h"
#include "core/utility/NonAssignable.h"


namespace EmeraldEngine {
	class Application {
	public:
		virtual void update(double deltaTime) = 0;
	};

	Application* createApplication(NonAssignable<Window> gameWindow, NonAssignable<ResourceManager> resourceManager);
}
