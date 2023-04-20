#pragma once
#include "_Core.h"
#include "utility.h"

namespace core {

    class GameObject;
    class Camera;
    class Layer;

    class Scene {
        friend class Application;
    public:
        std::vector<GameObject*> gameObjects;

        Scene();
        virtual ~Scene() = default;

        Shr<Camera> GetCamera();
        glm::vec4& GetBackcolor();

        void Start();
        void Stop();


        void AddLayer(Layer* layer);
        void AddOverlay(Layer* layer);
        void RemoveLayer(Layer* layer) const;
        void RemoveOverlay(Layer* layer) const;

    protected:
        Shr<Camera> camera = nullptr;
        glm::vec4 backcolor = {};

        virtual void OnStart() = 0;
        virtual void OnStop() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& e) = 0;
        virtual void Imgui(float dt) {}

    private:
        bool isRunning = false;

        void Update();

    };

}