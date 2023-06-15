#include "_Game.h"

#include "GameOverScene.h"
#include "../GameScene/GameScene.h"
#include "layers/StatLayer.h"

Shr<Sound> GameOverScene::sound_game_over;

void GameOverScene::Init()
{
    sound_game_over = MakeShr<Sound>();

    sound_game_over->LoadSound("assets/sounds/death.wav");
}

GameOverScene::GameOverScene() {
    backcolor = background_color;

    statLayer = new StatLayer();

    CreateButton("play_object_001.png", glm::vec2(0.0f, -1.0f), "play");
    CreateButton("../GameOverMenu/main_menu.png", glm::vec2(0.0f, -3.0f), "main-menu");
    
}

GameOverScene::~GameOverScene() {
}

void GameOverScene::OnStart() {
    AddLayer(statLayer);
}

void GameOverScene::OnStop() {
    RemoveLayer(statLayer);
    sound_game_over->StopSound();
}

void GameOverScene::OnUpdate() {
    sound_game_over->SoundPlay();
}

GameObject* GameOverScene::CreateButton(std::string sprite_name, glm::vec2 position, std::string action) {

    GameObject* button = new GameObject("menu_button", Transform(position, button_size));
    button->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("MainMenu/" + sprite_name), 1.0f, Geometry::RECTANGLE, true));
    button->AddTag(action);
    statLayer->AddGameObjectToLayer(button);
    return button;
}
