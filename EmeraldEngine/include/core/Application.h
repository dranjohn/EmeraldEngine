#pragma once

namespace EmeraldEngine {
	class Application {
	public:
		virtual void initialize() = 0;
		virtual void terminate() = 0;
	};

	Application* createApplication();
}
