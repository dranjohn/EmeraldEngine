#pragma once

//--- Interface files ---
#include "core/input/KeyCode.h"
#include "core/input/MousePosition.h"


namespace EmeraldEngine {
	struct WindowProperties {
		unsigned int width;
		unsigned int height;

		std::string title;

		bool resizable;
		bool continueRunning;

		WindowProperties(unsigned int width, unsigned int height, std::string title, bool resizable, bool continueRunning) :
			width(width),
			height(height),
			title(title),
			resizable(resizable),
			continueRunning(continueRunning)
		{}
	};

	std::shared_ptr<WindowProperties> getPropertyMemory();


	class Window {
	protected:
		Window() {}

	public:
		virtual void renderQuad() const = 0;
		virtual void setBackgroundColor(float red, float green, float blue) const = 0;

		virtual bool isKeyPressed(Key keyCode) const = 0;
		virtual bool isMouseButtonPressed(MouseButton mouseButtonCode) const = 0;
		virtual MousePosition getMousePosition() const = 0;
	};
}
