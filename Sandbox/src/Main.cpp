#include <memory>

#include <EmeraldEngine.h>


std::shared_ptr<EmeraldEngine::WindowProperties> windowProperties = std::make_shared<EmeraldEngine::WindowProperties>(
	640, 360, //dimension
	"Sandbox game", //title
	true //keep running
);

class Game : public EmeraldEngine::Application {
	void initialize() override {
		
	}

	void terminate() override {

	}


	void update(double deltaTime) override {
		EE_CLIENT_LOG_TRACE("Executing game iteration with {:.3f} seconds", deltaTime);
	}
};


EmeraldEngine::Application* EmeraldEngine::createApplication() {
	return new Game();
}

std::shared_ptr<EmeraldEngine::WindowProperties> EmeraldEngine::getPropertyMemory() {
	return windowProperties;
}
