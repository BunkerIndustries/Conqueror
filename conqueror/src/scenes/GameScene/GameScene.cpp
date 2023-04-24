#include "_Game.h"
#include "GameScene.h"

#include "required/constants.h"

#include "utils/Engineer.h"
#include "utils/Supply.h"

GameScene::GameScene() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    backgroundLayer = new BackgroundLayer();
    mapLayer = new MapLayer();
    enemyLayer = new EnemyLayer();
    allyLayer = new AllyLayer;
    uiLayer = new UILayer();

    waveManager = new WaveManager(this);
}

GameScene::~GameScene() {

}

void GameScene::OnStop() {
    RemoveLayer(backgroundLayer);
    RemoveLayer(mapLayer);
    RemoveLayer(enemyLayer);
    RemoveLayer(allyLayer);

    RemoveOverlay(uiLayer);
}
void GameScene::OnStart() {

    Supply::Init();

    AddLayer(backgroundLayer);
    AddLayer(mapLayer);
    AddLayer(enemyLayer);
    AddLayer(allyLayer);

    AddOverlay(uiLayer);
}

void GameScene::OnUpdate() {

    CameraMovement(Application::GetDT());
    waveManager->OnUpdate();
}

void GameScene::CameraMovement(float dt) {
    if (Input::IsKeyPressed(KEY_S) && camera->position.y > min_camera_positions.y) 
        camera->position.y -= camera_move_speed * dt;
    if (Input::IsKeyPressed(KEY_W) && camera->position.y < max_camera_positions.y)
        camera->position.y += camera_move_speed * dt;
    if (Input::IsKeyPressed(KEY_D) && camera->position.x < max_camera_positions.x)
        camera->position.x += camera_move_speed * dt;
    if (Input::IsKeyPressed(KEY_A) && camera->position.x > min_camera_positions.x)
        camera->position.x -= camera_move_speed * dt;
}

bool GameScene::OnMouseScroll(MouseScrolledEvent& e)
{
    //Checking if camera z position is inside wanted bounds
    if (GetCamera()->position.z > max_camera_z_pos && e.GetYOffset() > 0) return true;
    else if (GetCamera()->position.z < min_camera_z_pos && e.GetYOffset() < 0) return true;
    GetCamera()->position.z += camera_scroll_speed * Application::GetDT() * e.GetYOffset();

    return true;
}

bool GameScene::GameObjectPressed(GameObjectPressedEvent& e) {

    return true;
}
