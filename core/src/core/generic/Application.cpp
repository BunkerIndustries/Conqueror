#include "_Core.h"

#include "generic/Application.h"

#include "event/Input.h"
#include "event/KeyCodes.h"
#include "event/GameEvent.h"
#include "renderer/RenderCommand.h"
#include "renderer/Renderer.h"
#include "imgui/ImGuiLayer.h"
#include "utils/Core.h"


namespace core {

	Application* Application::instance;

	Application::Application() {
		Log::Init();
		CORE_ASSERT(!instance, "application is already instanced!");
		instance = this;

		Core::Init();

		window = Window::Create();
		SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		imguiLayer = new ImGuiLayer();
	}

	Application::~Application()
	{
		Exit();
	}

	void Application::Init() { }

	void Application::QueueEvents(Event* event)
	{
		GetInstance()->eventQueue.emplace(GetInstance()->eventQueue.begin(), event);
	}


	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));

		if (event.IsInCategory(EventCategoryGameObject))
		{
			if (const GameObject* gm = (*dynamic_cast<GameObjectEvent*>(&event)).GetGameObject(); gm->onlyLayerReceive)
			{
				gm->GetLayer()->OnEvent(event);
				return;
			}
		}

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			if (event.handled)
				break;
			--it;
			if ((*it)->IsAttached())
				(*it)->LayerEvent(event);
		}
		if (!event.handled)
		{
			currentScene->OnEvent(event);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		gameRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		resizing = true;
		Renderer::ResizeWindow(e.getWidth(), e.getHeight());
		window->Resize(e.getWidth(), e.getHeight());
		return false;
	}


	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if (!e.getRepeated() && e.getKeyCode() == KEY_P)
		{
			return false;
			if (imguiEnabledQueue == 0 && imguiEnabled) imguiEnabledQueue = 1;
			else imguiEnabledQueue = 2;
		}
		if (e.getKeyCode() == KEY_F11)
		{
			return false;
			fullscreen = !fullscreen;
			window->EnableFullscreen(fullscreen);
		}
		return false;
	}

	void Application::ProcessQueues()
	{
		if (imguiEnabledQueue > 0)
		{
			imguiEnabled = imguiEnabledQueue - 1;
			imguiEnabledQueue = 0;
		}

		for (Event* event : eventQueue)
		{
			OnEvent(*event);
			delete event;
		}
		eventQueue.clear();
	}

	void Application::Run() 
	{
		DataPool::GetFont("mononoki.ttf");
		Init();

		AddOverlay(imguiLayer);


		//set start scene
		if (queuedScene) {
			currentScene = queuedScene;
			currentScene->Start();
			queuedScene = nullptr;
		}

		// start of the calculations
		float begin_time = window->GetTime();
		dt = 0.0167f;
		bool warn = true;

		while (gameRunning)
		{
			window->PollEvents();
			ProcessQueues();

			//MouseListener::resetValues();
			if (currentScene != nullptr) {
				// request color
				RenderCommand::ClearColor(currentScene->GetBackcolor());
				

				if (dt >= 0) {
					if (queuedScene != nullptr) {
						// TODO: save scenes instead of deleting them
						// delete the scene with it's heap components (renderer and camera)
						currentScene->Stop();

						// remove the scene
						if (deleteOldScene)
						{
							delete currentScene;
							deleteOldScene = false;
						}
						// switch and initialize the scene
						currentScene = queuedScene;
						currentScene->Start();
						// don't forget to reset the tempscene, because we want to override it
						queuedScene = nullptr;
					}

					imguiLayer->Begin(dt);

					for (Layer* layer : layerStack)
					{
						if (layer->IsAttached())
							layer->Update(dt);
					}

					currentScene->Update();

					Input::ProcessInput();
					
					if (imguiEnabled) {
					
						for (Layer* layer : layerStack) {
							layer->Imgui(dt);
						}
					}
					else
					{
						imguiLayer->ScreenPanel();
					}

					imguiLayer->End();
				}
			}
			else if (warn) {
				LOG_CORE_ERROR("No Scene exists. Make sure to call Application::changeScene() in the 'init' function of your Application class");
				warn = false;
			}

			window->SwapBuffers();

			imguiEnabledBefore = imguiEnabled;
			resizing = false;

			dt = window->GetTime() - begin_time;
			if (dt > 0.1f) dt = 0.0167;
			begin_time = window->GetTime();
		}

		LOG_CORE_WARN("Reached end of game function. Shutting down.");
	}

	void Application::ChangeScene(Scene* new_scene)
	{
		GetInstance()->queuedScene = new_scene;
	}

	void Application::ChangeScene(Scene* new_scene, bool deleteOldScene)
	{
		GetInstance()->queuedScene = new_scene;
		GetInstance()->deleteOldScene = deleteOldScene;
	}

	void Application::AddLayer(Layer* layer)
	{
		GetInstance()->layerStack.AddLayer(layer);
		if (!layer->IsAttached())
			layer->Attach();
	}

	void Application::AddOverlay(Layer* layer)
	{
		GetInstance()->layerStack.AddOverlay(layer);
		if (!layer->IsAttached())
			layer->Attach();
	}

	void Application::RemoveLayer(Layer* layer)
	{
		if (layer->IsAttached())
			layer->Detach();
		GetInstance()->layerStack.RemoveLayer(layer);
	}

	void Application::RemoveOverlay(Layer* layer)
	{
		if (layer->IsAttached())
			layer->Detach();
		GetInstance()->layerStack.RemoveOverlay(layer);
	}
}
