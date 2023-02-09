#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"
#include "generic/GameObject.h"

namespace core
{

	class CORE_API Layer
	{
	protected:
		std::string name;
		bool overlay = false;
		bool attached = false;

		std::vector<GameObject*> game_objects;

	public:
		Layer(const std::string& name = "Layer")
			: name(name) { }

		virtual ~Layer() = default;

		void attach(bool add_to_renderer);
		void detach();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void update(const float dt) = 0;
		virtual void imgui(const float dt) = 0;
		virtual void OnEvent(Event& event) = 0;

		void event(Event& event);

		void AddGameObjectToLayer(GameObject* game_object);

		void setOverlayStatus(bool overlay) { this->overlay = overlay; }

		bool getOverlayStatus() { return overlay; }
		std::vector<GameObject*> GetGameObjects() const { return game_objects; }
		std::string GetName() { return name; }
	};
}

