#include "_Game.h"
#include "GameScene.h"

#include "required/constants.h"

#include "utils/Engineer.h"
#include "utils/SoldierSupply.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
    RemoveLayer(mapLayer);
    RemoveLayer(enemyLayer);
    RemoveLayer(allyLayer);
    
    RemoveOverlay(uiLayer);
}

void GameScene::LoadResources() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    mapLayer = new MapLayer();
    enemyLayer = new EnemyLayer();
    allyLayer = new AllyLayer;
    uiLayer = new UILayer();

    waveManager = new WaveManager(this);
}
void GameScene::Init() {

    SoldierSupply::Init();

    AddLayer(mapLayer);
    AddLayer(enemyLayer);
    AddLayer(allyLayer);

    AddOverlay(uiLayer);
}

void GameScene::Update() {

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
    else if (clicked_go->HasTag("medic_building") || clicked_go->HasTag("engineer_building")) {
        if (active_go != nullptr && (active_go->HasTag("medic_building") || active_go->HasTag("engineer_building"))) active_go->GetComponent<BuildingUI>()->DeleteUI();
        clicked_go->GetComponent<BuildingUI>()->ToggleUI();
        active_go = clicked_go;
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
