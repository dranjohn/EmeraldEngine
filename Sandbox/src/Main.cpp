#include <EmeraldEngine.h>


class Game : public EmeraldEngine::Application {
private:
	EmeraldEngine::NonAssignable<EmeraldEngine::Window> gameWindow;

	bool showQuad = true;

public:
	Game(EmeraldEngine::NonAssignable<EmeraldEngine::Window>& gameWindow) : gameWindow(gameWindow) {
		gameWindow->setBackgroundColor(0.2f, 0.5f, 0.8f);

		gameWindow->getEventCallbacks().resizeCallback = [](const EmeraldEngine::WindowDimensions2D& windowDimensions) {
			EE_CLIENT_LOG_INFO("Window resize tp {}x{}", windowDimensions.width, windowDimensions.height);
		};
		gameWindow->getEventCallbacks().keyCallback = [&](EmeraldEngine::Key key, EmeraldEngine::KeyAction keyAction) {
			if (keyAction != EmeraldEngine::KeyAction::press) {
				return;
			}

			if (key == EmeraldEngine::Key::R) {
				gameWindow->resize(640, 360);
				return;
			}

			if (key == EmeraldEngine::Key::T) {
				showQuad = !showQuad;
				return;
			}

			if (key == EmeraldEngine::Key::escape) {
				gameWindow->close();
				return;
			}
		};

		std::weak_ptr<EmeraldEngine::Shader> shader = gameWindow->createShader("./res/shader/texture");
		shader.lock()->use();

		std::weak_ptr<EmeraldEngine::Texture> texture = gameWindow->loadTexture("./res/texture/color_test_image.png", EmeraldEngine::TextureFilter::nearest);
		texture.lock()->use(0);

		shader.lock()->loadTexture("plainTexture", 0);
	}

	void update(double deltaTime) override {
		//EE_CLIENT_LOG_TRACE("Executing game iteration with {:.3f} seconds", deltaTime);

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
