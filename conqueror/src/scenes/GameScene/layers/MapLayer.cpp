#include "_Game.h"

#include "MapLayer.h"

#include "required/maps.h"
#include "required/stands.h"

#include "utils/Engineer.h"
#include "utils/Medic.h"



MapLayer::MapLayer()
	: Layer("MapLayer")
{

}

MapLayer::~MapLayer()
{
}

void MapLayer::OnAttach()
{
	CreateGameMap(standard_map);
	CreateEnemyGrid(enemy_grid_x, enemy_grid_y, enemy_grid_offset, enemy_grid_startpos);


	Medic::AddBuilding(Transform(glm::vec2(12.0f, -5.0f), glm::vec2(1.0f), -45.0f), medic_count);
	Engineer::AddBuilding(Transform(glm::vec2(-12.0f, -5.0f), glm::vec2(1.0f), 45.0f), engineer_count);
}

void MapLayer::OnDetach()
{
}

void MapLayer::Update(const float dt)
{
}

void MapLayer::OnEvent(Event& event)
{
}


GameObject* MapLayer::CreateNode(glm::vec2 position, Stand& node_stand) {
	GameObject* node_go = new GameObject("node", Transform(position, node_size));

	node_go->AddComponent(new SpriteRenderer(*node_stand.color, Geometry::RECTANGLE));
	node_go->AddComponent(new Node(node_stand.stand));

	if (node_stand.stand != waiting_stand.stand) node_go->AddTag("move_node");
	else {
		waiting_nodes.push_back(node_go);
	}

	AddGameObjectToLayer(node_go);

	return node_go;
}

void MapLayer::CreateGameMap(std::vector<std::pair<std::vector<glm::vec2>, Stand>>& stands_with_nodes) {
	// for every stand (vector of its node-positions)
	for (auto& node : stands_with_nodes) {

		Stand s = node.second;

		// for every node-position in that stand
		for (auto& pos : node.first) {
			// create a node belonging to the stand with the desired position
			CreateNode(pos, s);
		}
	}
}

// TODO: Change to vec2 2D-vector, cubes are placeholders for debugging and visualisation
void MapLayer::CreateEnemyGrid(const uint8_t x_size, const uint8_t y_size, const float offset, const glm::vec2 mid_pos) {

	std::vector<std::vector<GameObject*>> grid;	//create 2D vector
	float cube_rad = 0.25f;
	glm::vec2 whole_len = glm::vec2(x_size * cube_rad * 2.0f + (x_size - 1) * offset, y_size * cube_rad * 2.0f + (y_size - 1) * offset);		//length of all cubes + offsets between
	glm::vec2 start_pos = glm::vec2(mid_pos.x - whole_len.x / 2.0f, mid_pos.y + whole_len.y / 2.0f);	// starts top left

	for (size_t x = 0; x < x_size; x++) {
		std::vector<GameObject*> y_row;	// create new y row vector 
		for (size_t y = 0; y < y_size; y++) {
			y_row.push_back(new GameObject(std::to_string(x) + std::to_string(y),
				Transform(glm::vec2(start_pos.x + x * (offset + cube_rad * 2.0f), start_pos.y - y * (offset + 2.0f * cube_rad)),
					glm::vec2(2 * cube_rad))));	// add gameobjects to it

			y_row.at(y)->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), Geometry::RECTANGLE));	// add SpriteRenderer
			y_row.at(y)->AddComponent(new Node(nullptr));
			//y_row.at(y)->AddTag("move_node");
			AddGameObjectToLayer(y_row.at(y));
		}
		grid.emplace_back(y_row);	// add y_row to grid at index x
	}
	enemy_grid = grid;
}

GameObject* MapLayer::CreateBuilding(Transform transform, std::string type) {

	GameObject* building = new GameObject(type + "-building", transform);

	if (type == "medic") {
		building->AddComponent(new SpriteRenderer(glm::vec4(0.05f, 0.05f, 0.05f, 1.0f), Geometry::RECTANGLE));	// temp: replace with correct sprite-path
		building->AddTag("medic-building");
	}
	else if (type == "engineer") {
		//building->AddComponent(engineer_management);
		building->AddComponent(new SpriteRenderer(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), Geometry::RECTANGLE));
		building->AddTag("engineer_building");
	}
	else {
		LOG_WARN("WARNING: probably no existing type given when creating a building");
	}

	AddGameObjectToLayer(building);

	return building;
}