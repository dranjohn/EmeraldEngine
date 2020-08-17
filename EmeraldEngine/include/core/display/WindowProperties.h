#pragma once

//--- Standard library ---
#include <functional>
#include <memory>
#include <string>

//--´- Interface files ---
#include "core/input/InputData.h"
#include "core/input/KeyCode.h"


namespace EmeraldEngine {
	struct WindowDimensions2D {
		unsigned int width; unsigned int height;
	};


	struct WindowProperties {
		WindowDimensions2D dimensions;
		std::string title;

		bool resizable;
	};

	WindowProperties getInitialWindowProperties();


	struct WindowEventCallbacks {
		std::function<void(const WindowDimensions2D&)> resizeCallback = [](const WindowDimensions2D&) {};

		std::function<void(bool)> iconifyCallback = [](bool) {};
		std::function<void(bool)> maximizeCallback = [](bool) {};
		std::function<void(bool)> focusCallback = [](bool) {};

		std::function<void(Key, KeyAction)> keyCallback = [](Key, KeyAction) {};

		std::function<void(CursorPosition)> cursorPositionCallback = [](CursorPosition) {};
		std::function<void(MouseClick, CursorPosition)> mouseButtonCallback = [](MouseClick, CursorPosition) {};
	};


	struct WindowData {
		WindowProperties windowProperties;
		WindowEventCallbacks windowEventCallbacks;
	};
}
