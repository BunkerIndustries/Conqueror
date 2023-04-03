#include "_Game.h"
#define INCLUDE_MAIN
#include "EntryPoint.h"
#include "Engine.h"

#include "scenes/MenuScene/MenuScene.h"
#include "required/constants.h"

class Conqueror : public core::Application {
public:
	Conqueror() {
		
	}
	
	~Conqueror() {
		
	}

	void Init() override {
		Application::ChangeScene(menuScene);
	}

};

core::Application* core::CreateApplication() {
	return new Conqueror();
}