// THIS IS A HEADER FILE
#include "start_scene.h"

using namespace core;

StartScene::StartScene() {
}

// clear everything on destruction
StartScene::~StartScene() {
    // free layers
    //Application::RemoveLayer(background_layer);
    Application::RemoveLayer(foreground_layer);
    //Application::RemoveOverLay(sound_layer);
}

// init() is called after loudResources
// there is no difference

void StartScene::loadResources() {
    // set background color
    backcolor = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);

    // allocate layers
    //background_layer = new BackgroundLayer();
    foreground_layer = new ForegroundLayer();
    //sound_layer = new SoundLayer;
}
void StartScene::init() {
    //Application::AddLayer(background_layer);
    Application::AddLayer(foreground_layer);
    //Application::AddOverLay(sound_layer);
}


int selectedItem = 0;
void StartScene::update(float dt) {
    // here the input gets polled. This means, that you asks every frame "IS THIS KEY PRESSED OR NOT?!" and if so 'IsKeyPressed' returns true.

    if (Input::IsKeyPressed(KEY_S)) {
        camera->position.y -= 2.0f * dt;
    }
    if (Input::IsKeyPressed(KEY_W)) {
        camera->position.y += 2.0f * dt;
    }
    if (Input::IsKeyPressed(KEY_D)) {
        camera->position.x += 2.0f * dt;
    }
    if (Input::IsKeyPressed(KEY_A)) {
        camera->position.x -= 2.0f * dt;
    }


    //// adjust the size of the current gameobject
    //if (Input::IsKeyPressed(KEY_LEFT)) {
    //    activeGameObject->transform.scale.x += 2.0f * dt;
    //}
    //if (Input::IsKeyPressed(KEY_RIGHT)) {
    //    activeGameObject->transform.scale.x -= 2.0f * dt;
    //}
    //if (Input::IsKeyPressed(KEY_UP)) {
    //    activeGameObject->transform.scale.y += 2.0f * dt;
    //}
    //if (Input::IsKeyPressed(KEY_DOWN)) {
    //    activeGameObject->transform.scale.y -= 2.0f * dt;
    //}

    //// HERE YOU CAN CHANGE THE SCENE TO ANOTHER
    //// YOU JUST HAVE TO INCLUDE THE DESIRED SCENE HEADER, IN ORDER TO ALLOCATE SPACE AND FIND THE REFERENCE TO THE SWITCHING SCENE

    //if (Input::IsKeyPressed(KEY_U)) {
    //    Application::Get()->changeScene(new StartScene());
    //}

    // tell the renderer to use our created layers


    this->renderer->render(Application::GetLayerStack(), dt);
}

// YOU DO NOT HAVE TO CARE ABOUT THIS!!
void StartScene::imgui(float dt) {

}

// here is a function you can create and it gets called when the specified event is triggered
// the oject in the parameter of the function contains all the important information about the event
bool StartScene::OnMouseScroll(MouseScrolledEvent& e)
{
    /*if (this->getCamera()->position.z > 1)
        this->getCamera()->position.z += 10.0f * core::Application::GetDT() * e.getYOffset();
    else if (e.getYOffset() > 0)
        this->getCamera()->position.z += 10.0f * core::Application::GetDT() * e.getYOffset();
    this->getCamera()->fov += 1.0f * core::Application::GetDT() * e.getXOffset();*/
    return true;
}

// ALSO IF YOU DID NOT KNOW HOW C++ WORKS, YOU CAN ALSO ADD FUNCTIONS, BUT YOU HAVE TO DEFINE THEM IN THE BELONGING HEADER FILE
