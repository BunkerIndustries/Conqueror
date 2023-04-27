#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Window.h"
#include "generic/Scene.h"
#include "layer/Layer.h"
#include "layer/LayerStack.h"

#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"



namespace core {

	class ImGuiLayer;

	class Application
	{
	private:
		static Application* instance;
		Shr<Window> window = nullptr;
		ImGuiLayer* imguiLayer = nullptr;
		Scene* currentScene = nullptr;
		Scene* queuedScene = nullptr;
		std::vector<Event*> eventQueue;
		float dt;
		long int framesRendered = 0;
		bool gameRunning = true;
		bool resizing = false;

		//IMGUI
		bool imguiEnabled = false; int imguiEnabledQueue = 0;
		bool imguiEnabledBefore = imguiEnabled;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		void ProcessQueues();

		friend class Scene;
		static void AddLayer(Layer* layer);
		static void AddOverlay(Layer* layer);
		static void RemoveLayer(Layer* layer);
		static void RemoveOverlay(Layer* layer);

		LayerStack layerStack;

	public:

		Application();
		virtual ~Application();

		virtual void Init();
		
		void Run();

		void OnEvent(Event& event);

		static void ChangeScene(Scene* new_scene);

		void Exit() { gameRunning = false; }

		static void QueueEvents(Event* event);
		static Application* GetInstance() { return instance; }

		static long int GetFramesRendered() { return GetInstance()->framesRendered; }
		static bool GetImGuiEnabled() { return GetInstance()->imguiEnabled; }
		static bool GetImGuiSwitched() { return GetInstance()->imguiEnabledBefore != GetInstance()->imguiEnabled; }
		static float GetDT() { return GetInstance()->dt; }
		static bool IsResizing() { return GetInstance()->resizing; }
		static void SetEventCallback(const EventCallbackFunction& callbackFunction) { GetInstance()->window->SetEventCallback(callbackFunction); }

		static Shr<Window> GetWindow() { return GetInstance()->window; }
		static Scene* GetActiveScene() { return GetInstance()->currentScene; }
		static ImGuiLayer& GetImGuiLayer() { return *GetInstance()->imguiLayer; }
		static LayerStack& GetLayerStack() { return GetInstance()->layerStack; }

		virtual void GameObjectDeleted(GameObject* gameObject) {};
	};

	//defined by client
	Application* CreateApplication();
}

