#include "start_scene.h"
#include "required/constants.h"
#include "required/functions.h"
#include <vector>

#include "components/movement.h"

using namespace core;

StartScene::StartScene() {
}

StartScene::~StartScene() {
    //Application::RemoveLayer(background_layer);
    Application::RemoveLayer(foreground_layer);
    //Application::RemoveOverLay(sound_layer);
}

void StartScene::loadResources() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

    //background_layer = new BackgroundLayer();
    foreground_layer = new ForegroundLayer();
    //sound_layer = new SoundLayer;

    //Grid creation
    std::vector<std::vector<GameObject*>> enemy_grid = CreateGrid(5, 5, 2.0f, glm::vec2(0.0f, 0.0f), foreground_layer);

    test = new GameObject("test", Transform(glm::vec2(0.0f, 0.0f), glm::vec2(1.0, 1.0f)));
    test->addComponent(new SpriteRenderer(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    test->addComponent(new Movement());
    LOG_DEBUG("Start x pos: {0}", test->transform.position.x);
    ((Movement*)test->getComponent("movement"));
    foreground_layer->AddGameObjectToLayer(test);
}
void StartScene::init() {
    //Application::AddLayer(background_layer);
    Application::AddLayer(foreground_layer);
    //Application::AddOverLay(sound_layer);
}


int selectedItem = 0;
void StartScene::update(float dt) {

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

    if (Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        
        ((Movement*)test->getComponent("movement"))->target_pos = glm::vec2(5.0f, 5.0f);
    }

    this->renderer->render(dt);
}

void StartScene::imgui(float dt) {

}

bool StartScene::OnMouseScroll(MouseScrolledEvent& e)
{
    //Checking if camera z position is inside wanted bounds
    if (getCamera()->position.z > maxCameraZPos && e.getYOffset() > 0) return false;
    else if (getCamera()->position.z < minCameraZPos && e.getYOffset() < 0) return false;
    getCamera()->position.z += cameraScrollSpeed * Application::GetDT() * e.getYOffset();

    return true;
}