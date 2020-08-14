#pragma once

//--- Interface files ---
#include "core/display/Window.h"


namespace EmeraldEngine {
	class InternalWindow : public Window {
	protected:
		InternalWindow() {}

	public:
		virtual void resetTime() = 0;
		virtual double getTime() = 0;

		virtual void preUpdate() = 0;
		virtual void postUpdate() = 0;
	};
}
