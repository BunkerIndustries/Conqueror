#define INCLUDE_MAIN
#include "Engine.h"

#include "scenes/StartScene/start_scene.h"

class Conqueror : public core::Application {
public:
	Conqueror() {
		
	}
	
	~Conqueror() {
		
	}

	void init() override {
		Application::changeScene(new StartScene());
	}

};

core::Application* core::createApplication() {
	return new Conqueror();
}