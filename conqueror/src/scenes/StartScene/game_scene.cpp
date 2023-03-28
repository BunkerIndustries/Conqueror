#include "_Game.h"
#include "game_scene.h"

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/movement.h"
#include "components/soldier_behaviour.h"
#include "components/wave_manager.h"
#include "required/map_creation.h"

using namespace core;

GameScene::GameScene() {
}

GameScene::~GameScene() {
    //Application::RemoveLayer(background_layer);
    RemoveLayer(foreground_layer);
    //Application::RemoveOverLay(sound_layer);
}

void GameScene::LoadResources() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    //background_layer = new BackgroundLayer();
    //sound_layer = new SoundLayer;

    //Grid creation
    enemy_grid = CreateEnemyGrid(enemy_grid_x, enemy_grid_y, enemy_grid_offset, enemy_grid_startpos);

    GameObject* character = CreateSoldier(glm::vec2(-5.0f, -5.0f));
    GameObject* character2 = CreateSoldier(glm::vec2(-4.0f, -5.0f));

    /*GameObject* enemy = CreateEnemy("enemy 1", glm::vec2(1.0f, 10.0f));
    GameObject* enemy2 = CreateEnemy("enemy 2", glm::vec2(-1.0f, 10.0f));*/

    GameObject* empty_wave_manager = new GameObject("wave_manager", Transform(glm::vec2(0.0f), glm::vec2(0.0f)));
    empty_wave_manager->AddComponent(new WaveManager());
    foreground_layer->AddGameObjectToLayer(empty_wave_manager);

    GameObject* medic_building = CreateBuilding(glm::vec2(12.0f, -5.0f), "medic");
    GameObject* engineer_building = CreateBuilding(glm::vec2(-12.0f, -5.0f), "engineer");

    CreateGameMap(standard_map);
}
void GameScene::Init() {
    //Application::AddLayer(background_layer);
    AddLayer(foreground_layer);
    //Application::AddOverLay(sound_layer);
}


int selectedItem = 0;
void GameScene::Update() {

    float dt = Application::GetDT();
    
    CameraMovement(dt);
}

void GameScene::CameraMovement(float dt) {
    if (Input::IsKeyPressed(KEY_S)) {
        camera->position.y -= cameraMoveSpeed * dt;
    }
    if (Input::IsKeyPressed(KEY_W)) {
        camera->position.y += cameraMoveSpeed * dt;
    }
    if (Input::IsKeyPressed(KEY_D)) {
        camera->position.x += cameraMoveSpeed * dt;
    }
    if (Input::IsKeyPressed(KEY_A)) {
        camera->position.x -= cameraMoveSpeed * dt;
    }
}



void GameScene::Imgui(float dt) {

}

bool GameScene::OnMouseScroll(MouseScrolledEvent& e)
{
    //Checking if camera z position is inside wanted bounds
    if (GetCamera()->position.z > maxCameraZPos && e.GetYOffset() > 0) return false;
    else if (GetCamera()->position.z < minCameraZPos && e.GetYOffset() < 0) return false;
    GetCamera()->position.z += cameraScrollSpeed * Application::GetDT() * e.GetYOffset();

    return true;
}

bool GameScene::GameObjectPressed(GameObjectPressedEvent& e) {
    //LOG_DEBUG("GameObjectPressed()");
    // select character or move it
    GameObject* clicked_go = e.GetGameObject();

    // If a character was clicked: active_gameobject that's supposed to move is set to that
    if (clicked_go->HasTag("soldier") && !clicked_go->GetComponent<SoldierBehaviour>()->on_spawn_pos) {
        if (active_go != nullptr && active_go->HasTag("soldier") && active_go != clicked_go) {
            active_go->GetComponent<CharacterUI>()->DeleteUI();
        }

        active_go = e.GetGameObject();
        active_go->GetComponent<CharacterUI>()->ToggleUI();
        
        return true;
    }
    // Else if a move_node was clicked: set the active_gameobject's target_position to the move_node's position
    else if (clicked_go->HasTag("move_node") && active_go != nullptr) {
        if (!clicked_go->GetComponent<Node>()->is_occupied) {
            active_go->GetComponent<SoldierBehaviour>()->SoldierMove(clicked_go);
            return true;
        }
        
    }

    return true;
}
