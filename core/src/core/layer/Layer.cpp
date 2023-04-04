#include "_Core.h"

#include "layer/Layer.h"
#include "event/Event.h"

namespace core
{
	Layer::~Layer()
	{
		const int layerSize = gameObjects.size();
		for (int i = 0; i < layerSize; i++)
		{
			if (gameObjects.size() > 0)
				delete gameObjects[0];
		}
		gameObjects.clear();
	}

	void Layer::Attach()
	{
		attached = true;
		for (GameObject* game_object : gameObjects)
		{
			game_object->Start();
		}
		OnAttach();
	}

	void Layer::Detach()
	{
		attached = false;
		for (GameObject* game_object : gameObjects)
		{
			game_object->Stop();
		}
		OnDetach();
	}

	void Layer::LayerEvent(Event& event)
	{
		for (GameObject* gm : gameObjects)
		{
			if (!gm->IsRunning()) continue;
			if (!event.handled)
			{
				gm->OnEvent(event);
			}
		}
		if (!event.handled)
		{
			OnEvent(event);
		}
	}


	void Layer::AddGameObjectToLayer(GameObject* gameObject)
	{
	if (attached) {
			gameObjects.push_back(gameObject);
			gameObject->Start();
		}
		else {
			gameObjects.push_back(gameObject);
		}
		gameObject->SetLayer(this);
	}

	std::vector<GameObject*> Layer::GetGameObjectsByTag(std::initializer_list<std::string> tags)
	{
		std::vector<GameObject*> gos;
		for (int i = 0; i < gameObjects.size(); i++)
		{
			for (std::string tag : tags)
			{
				if (gameObjects[i]->HasTag(tag))
				{
					gos.push_back(gameObjects[i]);
					break;
				}
			}
		}
		return gos;
	}

	std::vector<GameObject*> Layer::GetGameObjectsByTag(std::string tag)
	{
		std::vector<GameObject*> gos;
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects[i]->HasTag(tag))
			{
				gos.push_back(gameObjects[i]);
			}
		}
		return gos;
	}
}
