#pragma once
#include "_Core.h"
#include "utility.h"

#include "generic/Window.h"
#include "generic/Scene.h"
#include "layer/Layer.h"
#include "layer/LayerStack.h"

#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"

#include "ImGui/ImGuiLayer.h"

namespace core {

	class CORE_API Application
	{
	private:
		static Application* instance;
		Window* window = nullptr;
		ImGuiLayer* imguilayer = nullptr;
		Scene* current_scene = nullptr;
		Scene* queued_scene = nullptr;
		std::vector<Event*> eventQueue;
		float dt;
		long int frames_rendered = 0;
		bool game_running = true;
		bool imgui_enabled = false; int imgui_enabled_queue = 0;

		bool onWindowClose(WindowCloseEvent& e);
		bool onKeyPressed(KeyPressedEvent& e);

		void ProcessQueues();

		LayerStack layer_stack;

	public:

		Application();
		virtual ~Application();

		virtual void init();
		
		void run();

		void onEvent(Event& event);

		static void AddLayer(Layer* layer, bool add_to_renderer = true);
		static void AddOverLay(Layer* layer, bool add_to_renderer = true);
		static void RemoveLayer(Layer* layer);
		static void RemoveOverLay(Layer* layer);

		static void ChangeScene(Scene* new_scene);

		void exit() { game_running = false; }

		static void QueueEvents(Event* event);
		static Application* GetInstance() { return instance; }

		static long int GetFramesRendered() { return GetInstance()->frames_rendered; }
		static bool GetImGuiEnabled() { return GetInstance()->imgui_enabled; }
		static float GetDT() { return GetInstance()->dt; }
		static void SetEventCallback(const EventCallbackFunction& callback_function) { GetInstance()->window->setEventCallback(callback_function); }

		static Window* GetWindow() { return GetInstance()->window; }
		static Scene* GetCurrentScene() { return GetInstance()->current_scene; }
		static ImGuiLayer& GetImGuiLayer() { return *GetInstance()->imguilayer; }
		static LayerStack& GetLayerStack() { return GetInstance()->layer_stack; }
	};
	
	//defined by client
	Application* createApplication();
}

