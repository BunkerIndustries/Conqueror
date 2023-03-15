#include "_Core.h"

#include "layer/Layer.h"
#include "generic/Application.h"
#include "event/Event.h"

namespace core
{
	void Layer::attach(bool add_to_renderer)
	{
		attached = true;
		for (GameObject* game_object : game_objects)
		{
			game_object->start();
		}
		OnAttach();
		if (add_to_renderer)
			Application::GetCurrentScene()->GetRenderer().add(this, Application::GetLayerStack().GetPlace(this));
	}

	void Layer::detach()
	{
		attached = false;
		for (GameObject* game_object : game_objects)
		{
			game_object->stop();
		}
		OnDetach();
	}

	void Layer::event(Event& event)
	{
		for (GameObject* gm : game_objects)
		{
			if (!gm->IsRunning()) continue;
			if (!event.handled)
			{
				gm->event(event);
			}
		}
		if (!event.handled)
		{
			OnEvent(event);
		}
	}


	void Layer::AddGameObjectToLayer(GameObject* game_object)
	{
		if (attached) {
			game_objects.push_back(game_object);
			if (game_object->GetComponent<SpriteRenderer>())
				Application::GetCurrentScene()->GetRenderer().add(game_object->GetComponent<SpriteRenderer>(), Application::GetLayerStack().GetPlace(this));
			game_object->start();
		}
		else {
			game_objects.push_back(game_object);
		}
		game_object->SetLayer(this);
	}

}
