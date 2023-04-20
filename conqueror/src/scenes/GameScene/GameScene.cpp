#include "_Game.h"
#include "GameScene.h"

#include "required/constants.h"

#include "utils/Engineer.h"
#include "utils/SoldierSupply.h"

GameScene::GameScene() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    mapLayer = new MapLayer();
    enemyLayer = new EnemyLayer();
    allyLayer = new AllyLayer;
    uiLayer = new UILayer();

    waveManager = new WaveManager(this);
}

GameScene::~GameScene() {

}

void GameScene::OnStop() {
    RemoveLayer(mapLayer);
    RemoveLayer(enemyLayer);
    RemoveLayer(allyLayer);

    RemoveOverlay(uiLayer);
}
void GameScene::OnStart() {

    SoldierSupply::Init();

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
    if (Input::IsKeyPressed(KEY_S)) 
        camera->position.y -= cameraMoveSpeed * dt;
    if (Input::IsKeyPressed(KEY_W))
        camera->position.y += cameraMoveSpeed * dt;
    if (Input::IsKeyPressed(KEY_D))
        camera->position.x += cameraMoveSpeed * dt;
    if (Input::IsKeyPressed(KEY_A))
        camera->position.x -= cameraMoveSpeed * dt;
}

bool GameScene::OnMouseScroll(MouseScrolledEvent& e)
{
    //Checking if camera z position is inside wanted bounds
    if (GetCamera()->position.z > maxCameraZPos && e.GetYOffset() > 0) return true;
    else if (GetCamera()->position.z < minCameraZPos && e.GetYOffset() < 0) return true;
    GetCamera()->position.z += cameraScrollSpeed * Application::GetDT() * e.GetYOffset();

    return true;
}

bool GameScene::GameObjectPressed(GameObjectPressedEvent& e) {

    return true;
}
