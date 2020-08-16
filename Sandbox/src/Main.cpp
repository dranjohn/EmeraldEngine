#include <memory>

#include <EmeraldEngine.h>


std::shared_ptr<EmeraldEngine::WindowProperties> windowProperties = std::make_shared<EmeraldEngine::WindowProperties>(
	640, 360, //dimension
	"Sandbox game", //title
	true, //resizable
	true //keep running
);

class Game : public EmeraldEngine::Application {
private:
	const EmeraldEngine::Window& gameWindow;

	bool showQuad = true;
	bool showSwap = false;

public:
	Game(const EmeraldEngine::Window& gameWindow) : gameWindow(gameWindow) {
		gameWindow.setBackgroundColor(0.2f, 0.5f, 0.8f);
	}

	void update(double deltaTime) override {
		EE_CLIENT_LOG_TRACE("Executing game iteration with {:.3f} seconds", deltaTime);

		if (gameWindow.isKeyPressed(EmeraldEngine::Key::escape)) {
			windowProperties->continueRunning = false;
			return;
		}
		
		if (gameWindow.isKeyPressed(EmeraldEngine::Key::T)) {
			if (!showSwap) {
				showQuad = !showQuad;
				showSwap = true;
			}
		}
		else {
			showSwap = false;
		}

		if (showQuad) {
			gameWindow.renderQuad();
		}
	}
};


EmeraldEngine::Application* EmeraldEngine::createApplication(const EmeraldEngine::Window& gameWindow) {
	return new Game(gameWindow);
}

std::shared_ptr<EmeraldEngine::WindowProperties> EmeraldEngine::getPropertyMemory() {
	return windowProperties;
}

EmeraldEngine::Platform EmeraldEngine::getPlatform() {
	return EmeraldEngine::Platform::defaultPlatform;
}
