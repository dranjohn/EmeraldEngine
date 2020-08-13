#include <memory>

#include <EmeraldEngine.h>


class Game : public EmeraldEngine::Application {
	void initialize() override {
		
	}

	void terminate() override {

	}
};


EmeraldEngine::Application* EmeraldEngine::createApplication() {
	return new Game();
}
