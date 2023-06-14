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
		menuScene = new MenuScene();

		DataPool::GetFont(ui_font_family);

		Application::ChangeScene(menuScene);
	}

	void GameObjectDeleted(GameObject* gameObject) override
	{
		if (gameObject->HasTag("enemy"))
		{
			for (size_t y = 0; y < enemy_grid_y; y++) {
				for (size_t x = 0; x < enemy_grid_x; x++)
				{
					if (enemy_stands[y][x] == gameObject) {
						enemy_stands[y][x] = nullptr;
					}
				}
			}

		}
	}
};

core::Application* core::CreateApplication() {
	return new Conqueror();
}