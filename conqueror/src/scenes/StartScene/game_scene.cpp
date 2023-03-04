#include "game_scene.h"
#include <vector>

#include "required/constants.h"
#include "required/functions.h"
#include "required/stands.h"
#include "components/movement.h"
#include "components/soldier_behaviour.h"

using namespace core;

GameScene::GameScene() {
}

GameScene::~GameScene() {
    //Application::RemoveLayer(background_layer);
    Application::RemoveLayer(foreground_layer);
    //Application::RemoveOverLay(sound_layer);
}

void GameScene::loadResources() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    //background_layer = new BackgroundLayer();
    //sound_layer = new SoundLayer;

    //Grid creation
    enemy_grid = CreateEnemyGrid(enemy_grid_x, enemy_grid_y, enemy_grid_offset, enemy_grid_startpos);

    GameObject* character = CreateCharacter("soldier", glm::vec2(0.0f, 0.0f));
    //GameObject* character2 = CreateCharacter("soldier", glm::vec2(1.0f, 1.0f));

    GameObject* enemy = CreateEnemy("enemy 1", glm::vec2(1.0f, 0.0f));
    GameObject* enemy2 = CreateEnemy("enemy 2", glm::vec2(-1.0f, 0.0f));

    GameObject* node = CreateNode(glm::vec2(0.0f, -3.0f), front_stand);
    GameObject* node2 = CreateNode(glm::vec2(1.0f, -3.0f), mg_stand);
    GameObject* node3 = CreateNode(glm::vec2(2.0f, -3.0f), trench_stand);
    GameObject* node4 = CreateNode(glm::vec2(3.0f, -3.0f), hiding_stand);
    GameObject* node5 = CreateNode(glm::vec2(4.0f, -3.0f), artillerie_stand);
    GameObject* node6 = CreateNode(glm::vec2(5.0f, -3.0f), bunker_stand);
    GameObject* node7 = CreateNode(glm::vec2(6.0f, -3.0f), waiting_stand);
}
void GameScene::init() {
    //Application::AddLayer(background_layer);
    Application::AddLayer(foreground_layer);
    //Application::AddOverLay(sound_layer);
}


int selectedItem = 0;
//bool m_pressed = false;    // is needed that pressing M doesn't trigger multiple times
void GameScene::update(float dt) {

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

    //if (Input::IsKeyPressed(KEY_M) && m_pressed == false) {
    //    m_pressed = true;
    //    LOG_DEBUG("M-PRESSED-------------------");
    //    glm::vec2 random_pos = enemy_grid.at(RandomInt(0, enemy_grid_x - 1)).at(RandomInt(0, enemy_grid_y - 1))->transform.position;      // needs to be changed if CreateGrid gets changed to returning an vec2-vector
    //    test->GetComponent<Movement>()->target_position = random_pos;
    //}
    //else if(!Input::IsKeyPressed(KEY_M)) m_pressed = false;

    this->renderer->render(dt);
}

void GameScene::imgui(float dt) {

}

bool GameScene::OnMouseScroll(MouseScrolledEvent& e)
{
    //Checking if camera z position is inside wanted bounds
    if (getCamera()->position.z > maxCameraZPos && e.getYOffset() > 0) return false;
    else if (getCamera()->position.z < minCameraZPos && e.getYOffset() < 0) return false;
    getCamera()->position.z += cameraScrollSpeed * Application::GetDT() * e.getYOffset();

    return true;
}

bool GameScene::GameObjectPressed(GameObjectPressedEvent& e) {

    // select character or move it
    GameObject* clicked_go = e.GetGameObject();

    // If a character was clicked: active_gameobject that's supposed to move is set to that
    if (clicked_go->HasTag("soldier")) {
        active_go = e.GetGameObject();
    }
    // Else if a move_node was clicked: set the active_gameobject's target_position to the move_node's position
    else if (clicked_go->HasTag("move_node") && !clicked_go->GetComponent<Node>()->is_occupied && active_go != nullptr) {
        active_go->GetComponent<SoldierBehaviour>()->SoldierMove(clicked_go);
    }

    return true;
}
