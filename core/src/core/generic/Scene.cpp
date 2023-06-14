#include "_Core.h"

#include "generic/Application.h"
#include "generic/Scene.h"
#include "generic/Camera.h"
#include "renderer/Renderer.h"


namespace core {

	Scene::Scene()
	{
		camera = std::make_shared<Camera>();
	}

	void Scene::Update()
	{
		OnUpdate();
		Renderer::ClearStats();
		Renderer::BeginRender(*camera);

		for (int i = 0; i < Application::GetLayerStack().GetSize(); i++)
		{
			Layer* layer = Application::GetLayerStack()[i];
			if (!layer->IsAttached()) continue;

			for (int j = 0; j < layer->GetGameObjects().size(); j++)
			{
				GameObject* gameObject = layer->GetGameObjects()[j];
				if (!gameObject->IsRunning()) continue;
				gameObject->Update();
			}
			Renderer::NextBatch();
			layer->RenderUI();
		}

		Renderer::EndRender();
	}

	void Scene::Start()
	{
		isRunning = true;
		OnStart();
	}

	void Scene::Stop()
	{
		isRunning = false;
		OnStop();
	}


	Shr<Camera> Scene::GetCamera() {
		// return the current scene camera, useful for scene testing
		return this->camera;
	}

	glm::vec4& Scene::GetBackcolor() {
		return this->backcolor;
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
}