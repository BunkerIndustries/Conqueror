#include "game_scene.h"
#include <vector>

#include "required/constants.h"
#include "required/functions.h"
#include "components/movement.h"

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
    foreground_layer = new ForegroundLayer();
    //sound_layer = new SoundLayer;

    //Grid creation
    enemy_grid = CreateGrid(enemy_grid_x, enemy_grid_y, enemy_grid_offset, enemy_grid_startpos, foreground_layer);

    test = new GameObject("test", Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0, 1.0f)));
    test->addComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    test->addComponent(new Movement());
    LOG_DEBUG("Start x pos: {0}", test->transform.position.x);
    ((Movement*)test->getComponent("movement"));
    foreground_layer->AddGameObjectToLayer(test);
}
void GameScene::init() {
    //Application::AddLayer(background_layer);
    Application::AddLayer(foreground_layer);
    //Application::AddOverLay(sound_layer);
}


int selectedItem = 0;
bool m_pressed = false;    // is needed that pressing M doesn't trigger multiple times
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

    if (Input::IsKeyPressed(KEY_M) && m_pressed == false) {
        m_pressed = true;
        LOG_DEBUG("M-PRESSED-------------------");
        glm::vec2 random_pos = enemy_grid.at(RandomInt(0, enemy_grid_x - 1)).at(RandomInt(0, enemy_grid_y - 1))->transform.position;      // needs to be changed if CreateGrid gets changed to returning an vec2-vector
        ((Movement*)test->getComponent("movement"))->target_position = random_pos;
    }
    else if(!Input::IsKeyPressed(KEY_M)) m_pressed = false;

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

    // if tag == gameobject 
    active_go = e.GetGameObject();

    // else if not tag == gameobject
    // if active_go exists: target_pos = clicked_object.position

    return true;
}