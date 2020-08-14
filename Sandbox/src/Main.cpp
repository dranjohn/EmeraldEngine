#include <memory>

#include <EmeraldEngine.h>


std::shared_ptr<EmeraldEngine::WindowProperties> windowProperties = std::make_shared<EmeraldEngine::WindowProperties>(
	640, 360, //dimension
	"Sandbox game", //title
	true //keep running
);

class Game : public EmeraldEngine::Application {
private:
	const EmeraldEngine::Window& gameWindow;

public:
	Game(const EmeraldEngine::Window& gameWindow) : gameWindow(gameWindow) {
		gameWindow.setBackgroundColor(0.2f, 0.5f, 0.8f);
	}

	void update(double deltaTime) override {
		EE_CLIENT_LOG_TRACE("Executing game iteration with {:.3f} seconds", deltaTime);
		gameWindow.renderQuad();
	}
};


EmeraldEngine::Application* EmeraldEngine::createApplication(const EmeraldEngine::Window& gameWindow) {
	return new Game(gameWindow);
}

std::shared_ptr<EmeraldEngine::WindowProperties> EmeraldEngine::getPropertyMemory() {
	return windowProperties;
}
