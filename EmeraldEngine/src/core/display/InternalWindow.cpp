#include "emeraldengine_pch.h"
#include "core/display/InternalWindow.h"

namespace EmeraldEngine {
	InternalWindow::InternalWindow(const WindowProperties& initialWindowProperties) :
		windowData({
			initialWindowProperties,
			WindowEventCallbacks()
		})
	{}
}
