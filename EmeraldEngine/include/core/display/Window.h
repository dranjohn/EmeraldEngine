#pragma once

//--- Interface files ---
#include "core/display/WindowProperties.h"
#include "core/input/InputData.h"
#include "core/input/KeyCode.h"


namespace EmeraldEngine {
	class Window {
	protected:
		Window() {}

	public:
		virtual void renderQuad() const = 0;
		virtual void setBackgroundColor(float red, float green, float blue) const = 0;

		virtual bool isKeyPressed(Key keyCode) const = 0;
		virtual bool isMouseButtonPressed(MouseButton mouseButtonCode) const = 0;
		virtual MousePosition getMousePosition() const = 0;

		virtual WindowProperties getWindowProperties() const = 0;
		virtual WindowEventCallbacks& getEventCallbacks() = 0;
	};
}
