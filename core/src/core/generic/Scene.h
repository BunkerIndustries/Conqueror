#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {

    class GameObject;
    class Camera;
    class Layer;

    class Scene {
    private:
        bool isRunning = false;
    protected:
        Camera* camera = nullptr;
        GameObject* activeGameObject = nullptr;
        glm::vec4 backcolor = glm::vec4();
    public:
        std::vector<GameObject*> gameObjects;

    public:
        Scene();
        virtual ~Scene();

        Camera* GetCamera();
        glm::vec4& GetBackcolor();

        void Start();
        void Disable();
        void InitGeneral();
        void OnUpdate();

        void AddLayer(Layer* layer);
        void AddOverlay(Layer* layer);
        void RemoveLayer(Layer* layer) const;
        void RemoveOverlay(Layer* layer) const;

        virtual void Update() = 0;
        virtual void OnEvent(Event& e) = 0;
    private:
        virtual void Imgui(float dt) {};
        virtual void Init() = 0;
        virtual void LoadResources() = 0;
    };

}