#define INCLUDE_MAIN
#include "Engine.h"

#include "scenes/Test/test.h"

class Conqueror : public core::Application {
public:
	Conqueror() {
		
	}
	
	~Conqueror() {
		
	}

	void init() override {
		Application::changeScene(new testScene());
	}

};

core::Application* core::createApplication() {
	return new Conqueror();
}