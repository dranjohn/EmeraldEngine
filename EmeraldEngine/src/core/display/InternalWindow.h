#pragma once

//--- Interface files ---
#include "core/display/Window.h"
#include "core/display/WindowProperties.h"


namespace EmeraldEngine {
	class InternalWindow : public Window {
	protected:
		WindowData windowData;

		InternalWindow(const WindowProperties& initialWindowProperties);

	public:
		virtual void resetTime() = 0;
		virtual double getTime() const = 0;

		virtual void preUpdate() = 0;
		virtual void postUpdate() = 0;

		virtual bool continueRunning() = 0;

		inline WindowProperties getWindowProperties() const override { return windowData.windowProperties; }
		inline WindowEventCallbacks& getEventCallbacks() override { return windowData.windowEventCallbacks; }
	};
}
