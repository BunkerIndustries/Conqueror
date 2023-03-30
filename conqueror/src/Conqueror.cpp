#include "_Game.h"
#define INCLUDE_MAIN
#include "EntryPoint.h"
#include "Engine.h"

#include "scenes/GameScene/GameScene.h"

class Conqueror : public core::Application {
public:
	Conqueror() {
		
	}
	
	~Conqueror() {
		
	}

	void Init() override {
		Application::ChangeScene(new GameScene());
	}

};

core::Application* core::CreateApplication() {
	return new Conqueror();
}