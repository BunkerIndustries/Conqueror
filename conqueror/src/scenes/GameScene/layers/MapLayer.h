#pragma once
#include "layer/Layer.h"

struct Stand;

class MapLayer : public Layer
{
public:

	MapLayer();
	~MapLayer() override;

	void OnAttach() override;
	void OnDetach() override;
	void Update(const float dt) override;
	void OnEvent(Event& e) override
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<GameObjectPressedEvent>(BIND_EVENT_FN(MapLayer::GameObjectPressed));
	};
	bool GameObjectPressed(GameObjectPressedEvent& e);

	GameObject* CreateBuilding(Transform transform, std::string type);
	GameObject* CreateNode(glm::vec2 position, Stand& node_stand);
	void CreateDeadBody(std::string sprite_path, glm::vec2 position);

	GameObject* CreateMg(glm::vec2 mg_position, GameObject* mg_node);
	GameObject* CreateArtillery(glm::vec2 artillery_position, GameObject* artillery_node);

	GameObject* medicBuilding;
	GameObject* engineerBuilding;
	GameObject* soldierBuilding;
private:
	void CreateGameMap(std::vector<std::pair<std::vector<glm::vec2>, Stand>>& stands_with_nodes, std::vector<std::pair<std::vector<Transform>, std::string>>& map_sprites);
	void CreateEnemyGrid(const uint8_t x_size, const uint8_t y_size, const float offset, const glm::vec2 mid_pos);
	void MapLayer::CreateMapSprite(std::string sprite_path, Transform trans);
	void MapLayer::RotateTrenchNodes();
};