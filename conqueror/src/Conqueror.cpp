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
		Application::GetWindow()->SetVSync(true);
		gameScene = new GameScene();
		menuScene = new MenuScene();

		DataPool::GetFont(ui_font_family);

		Application::ChangeScene(menuScene);
	}

};

core::Application* core::CreateApplication() {
	return new Conqueror();
}