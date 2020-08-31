#pragma once

//--- Standard library ---
#include <memory>

//--- Interface files ---
#include "core/display/WindowProperties.h"
#include "core/input/InputData.h"
#include "core/input/KeyCode.h"
#include "core/resourceManagement/shader/Shader.h"


namespace EmeraldEngine {
	class Window {
	protected:
		Window() {}

	public:
		virtual void renderQuad() const = 0;
		virtual void renderQuads(unsigned int amount) const = 0;

		virtual void setBackgroundColor(float red, float green, float blue) = 0;
		virtual void useFilter(std::weak_ptr<Shader> filter) = 0;
		virtual void clearFilter() = 0;

		virtual bool isKeyPressed(Key keyCode) const = 0;
		virtual bool isMouseButtonPressed(MouseButton mouseButtonCode) const = 0;
		virtual CursorPosition getCursorPosition() const = 0;

		virtual WindowProperties getWindowProperties() const = 0;
		virtual WindowEventCallbacks& getEventCallbacks() = 0;


		virtual void resize(unsigned int width, unsigned int height) = 0;
		virtual void setTitle(std::string title) = 0;

		virtual void close() = 0;
	};
}
