#pragma once

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
	};
}
