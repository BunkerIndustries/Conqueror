#include "_Core.h"

#include "imgui/ImGuiLayer.h"
#include "generic/Application.h"
#include "generic/Scene.h"
#include "generic/Camera.h"
#include "renderer/Renderer.h"


namespace core {

    Scene::Scene() {

    }

    Scene::~Scene() {
        delete camera;
    }

    void Scene::InitGeneral() {
        camera = new Camera();

        LoadResources();
        Init();
        Start();
    }

    void Scene::OnUpdate()
    {
        Update();
        Renderer::ClearStats();
        Renderer::BeginRender(*camera);

        //updating gameobjects and its components
        for (Layer* layer : Application::GetLayerStack())
        {
            if (!layer->IsAttached()) continue;
            for (GameObject* gameObject : layer->GetGameObjects())
            {
                if (!gameObject->IsRunning()) continue;
                gameObject->Update();
            }
        }

        Renderer::EndRender();
    }

    void Scene::AddLayer(Layer* layer)
    {
        layer->SetScene(this);
        Application::AddLayer(layer);
    }

    void Scene::AddOverlay(Layer* layer)
    {
        layer->SetScene(this);
        Application::AddOverlay(layer);
    }

    void Scene::RemoveLayer(Layer* layer) const
    {
        Application::RemoveLayer(layer);
    }

    void Scene::RemoveOverlay(Layer* layer) const
    {
        Application::RemoveOverlay(layer);
    }

    void Scene::Start() {
        isRunning = true;
    }

    void Scene::Disable() {
        delete camera;
    }

    Camera* Scene::GetCamera() {
        // return the current scene camera, useful for scene testing
        return this->camera;
    }

    glm::vec4& Scene::GetBackcolor() {
        return this->backcolor;
    }
}