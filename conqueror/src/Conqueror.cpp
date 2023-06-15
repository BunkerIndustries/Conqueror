#include "_Game.h"
#define INCLUDE_MAIN
#include "EntryPoint.h"
#include "Engine.h"

#include "scenes/MenuScene/MenuScene.h"
#include "required/constants.h"
#include "scenes/MenuScene/layers/MenuLayer.h"

#include "components/MedicComponent.h"
#include "components/ArtilleryComponent.h"
#include "utils/Engineer.h"
#include "utils/Supply.h"

class Conqueror : public core::Application {
public:
	Conqueror() {
		
	}
	
	~Conqueror() {
		
	}

	void Init() override {
		Application::GetWindow()->SetVSync(true);
		menuScene = new MenuScene();
		gameOverScene = new GameOverScene();

		DataPool::GetFont(ui_font_family);

		// god please forgive me
		Util::Init();
		MenuLayer::Init();
		Health::Init();
		EnemyShooting::Init();
		SoldierShooting::Init();
		MedicCharacter::Init();
		ArtilleryComponent::Init();
		EngineerCharacter::Init();
		AllyLayer::Init();
		MapLayer::Init();
		Engineer::Init();
		Supply::Init();
		WaveManager::Init();

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