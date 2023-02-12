#define INCLUDE_MAIN
#include "Engine.h"

#include "scenes/StartScene/game_scene.h"

class Conqueror : public core::Application {
public:
	Conqueror() {
		
	}
	
	~Conqueror() {
		
	}

	void init() override {
		Application::changeScene(new GameScene());
	}

};

core::Application* core::createApplication() {
	return new Conqueror();
}