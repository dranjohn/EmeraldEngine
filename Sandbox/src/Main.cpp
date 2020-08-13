#include <memory>

#include <EmeraldEngine.h>


EmeraldEngine::WindowProperties windowProperties = {
	640, 360,
	"Sandbox game"
};

class Game : public EmeraldEngine::Application {
	void initialize() override {
		
	}

	void terminate() override {

	}
};


EmeraldEngine::Application* EmeraldEngine::createApplication() {
	return new Game();
}

EmeraldEngine::WindowProperties& EmeraldEngine::getPropertyMemory() {
	return windowProperties;
}
