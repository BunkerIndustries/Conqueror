#include "_Game.h"
#define INCLUDE_MAIN
#include "EntryPoint.h"
#include "Engine.h"

#include "scenes/GameScene/game_scene.h"

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