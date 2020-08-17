#include <EmeraldEngine.h>


class Game : public EmeraldEngine::Application {
private:
	EmeraldEngine::NonAssignable<EmeraldEngine::Window> gameWindow;

	bool showQuad = true;
	bool showSwap = false;

public:
	Game(EmeraldEngine::NonAssignable<EmeraldEngine::Window>& gameWindow) : gameWindow(gameWindow) {
		gameWindow->setBackgroundColor(0.2f, 0.5f, 0.8f);

		gameWindow->getEventCallbacks().resizeCallback = [](const EmeraldEngine::WindowDimensions2D&) {
			EE_CLIENT_LOG_INFO("Window resize");
		};
	}

	void update(double deltaTime) override {
		//EE_CLIENT_LOG_TRACE("Executing game iteration with {:.3f} seconds", deltaTime);

		if (gameWindow->isKeyPressed(EmeraldEngine::Key::escape)) {
			return;
		}
		
		if (gameWindow->isKeyPressed(EmeraldEngine::Key::T)) {
			if (!showSwap) {
				showQuad = !showQuad;
				showSwap = true;
			}
		}
		else {
			showSwap = false;
		}

		if (showQuad) {
			gameWindow->renderQuad();
		}
	}
};


EmeraldEngine::Application* EmeraldEngine::createApplication(EmeraldEngine::NonAssignable<EmeraldEngine::Window> gameWindow) {
	return new Game(gameWindow);
}

EmeraldEngine::WindowProperties EmeraldEngine::getInitialWindowProperties() {
	return {
		{ 640, 360 }, //dimensions
		std::string("Sandbox game"), //title
		true //resizable
	};
}

EmeraldEngine::Platform EmeraldEngine::getPlatform() {
	return EmeraldEngine::Platform::defaultPlatform;
}
