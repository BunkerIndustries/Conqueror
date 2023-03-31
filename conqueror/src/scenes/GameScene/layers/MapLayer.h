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
	void OnEvent(Event& event) override;

	GameObject* CreateBuilding(Transform transform, std::string type);
	GameObject* CreateNode(glm::vec2 position, Stand& node_stand);
private:
	void CreateGameMap(std::vector<std::pair<std::vector<glm::vec2>, Stand>>& stands_with_nodes);
	void CreateEnemyGrid(const uint8_t x_size, const uint8_t y_size, const float offset, const glm::vec2 mid_pos);
};