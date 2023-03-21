#pragma once
#include "_Core.h"
#include "utility.h"

#include "event/Event.h"
#include "generic/GameObject.h"

namespace core
{

	class Layer
	{
	protected:
		std::string name;
		bool overlay = false;
		bool attached = false;

		std::vector<GameObject*> gameObjects;

	public:
		Layer(const std::string& name = "Layer")
			: name(name) { }

		virtual ~Layer() = default;

		void Attach();
		void Detach();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void Update(const float dt) = 0;
		virtual void Imgui(const float dt) { };
		virtual void OnEvent(Event& event) = 0;

		void LayerEvent(Event& event);

		void AddGameObjectToLayer(GameObject* game_object);

		void SetOverlayStatus(bool overlay) { this->overlay = overlay; }

		bool GetOverlayStatus() { return overlay; }
		std::vector<GameObject*>& GetGameObjects() { return gameObjects; }
		std::string GetName() { return name; }
	};
}