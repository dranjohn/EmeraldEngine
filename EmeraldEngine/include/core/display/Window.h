#pragma once

namespace EmeraldEngine {
	class Window {
	protected:
		Window() {}

	public:
		virtual void renderQuad() = 0;
	};
}
