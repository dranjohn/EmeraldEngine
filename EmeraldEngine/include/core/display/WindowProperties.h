#pragma once

//--- Standard library ---
#include <functional>
#include <memory>
#include <string>

//--´- Interface files ---
#include "core/input/InputData.h"


namespace EmeraldEngine {
	struct WindowDimensions2D {
		unsigned int width; unsigned int height;
	};


	struct WindowProperties {
		unsigned int width;
		unsigned int height;

		std::string title;

		bool resizable;
	};

	WindowProperties getInitialWindowProperties();


	struct WindowEventCallbacks {
		std::function<void()> resizeCallback = []() {};
	};


	struct WindowData {
		WindowProperties windowProperties;
		WindowEventCallbacks windowEventCallbacks;
	};
}
