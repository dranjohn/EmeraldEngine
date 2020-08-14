#pragma once

namespace EmeraldEngine {
	class Window {
	protected:
		Window() {}

	public:
		virtual void renderQuad() const = 0;
		virtual void setBackgroundColor(float red, float green, float blue) const = 0;
	};
}
