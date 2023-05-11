#include "_Game.h"

#include "MapLayer.h"

#include "required/maps.h"
#include "required/stands.h"

#include "utils/Engineer.h"
#include "utils/Medic.h"

#include "scenes/GameScene/GameScene.h"



MapLayer::MapLayer()
	: Layer("MapLayer")
{

}

MapLayer::~MapLayer()
{
}

void MapLayer::OnAttach()
{
	CreateGameMap(standard_map, standard_map_sprites);
	CreateEnemyGrid(enemy_grid_x, enemy_grid_y, enemy_grid_offset, enemy_grid_startpos);

	Layer* layer = this;
	medicBuilding = Medic::AddBuilding(Transform(glm::vec2(12.0f, -5.0f), building_size), start_medic_stock);
	engineerBuilding = Engineer::AddBuilding(Transform(glm::vec2(-12.0f, -5.0f), building_size), start_engineer_stock);
}

void MapLayer::OnDetach()
{
}

void MapLayer::Update(const float dt)
{
}

GameObject* MapLayer::CreateNode(glm::vec2 position, Stand& node_stand) {
	GameObject* node_go = new GameObject("node", Transform(position, node_size));

	node_go->AddComponent(new SpriteRenderer(*node_stand.color, Geometry::RECTANGLE));
	node_go->AddComponent(new Node(node_stand.stand));

	if (node_stand.stand == waiting_stand.stand) {
		waiting_nodes.push_back(node_go);
	}
	else if (node_stand.stand == trench_stand.stand) {
		trench_nodes.push_back(node_go);
		node_go->AddTag("move_node");
	}
	else if (node_stand.stand == hiding_stand.stand) {
		hiding_nodes.push_back(node_go);
		node_go->AddTag("move_node");
		CreateMapSprite("Map/walls_frontview.png", Transform(position + hiding_sprite_node_offset, hiding_sprite_size));

	}
	else {
		node_go->AddTag("move_node");
	}

	node_go->onlyLayerReceive = true;
	AddGameObjectToLayer(node_go);

	return node_go;
}

void MapLayer::CreateMapSprite(std::string sprite_path, Transform trans) {
	GameObject* sp = new GameObject("map_sprite", trans);
	sp->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture(sprite_path), 1.0f, Geometry::RECTANGLE));
	this->AddGameObjectToLayer(sp);
}

void MapLayer::CreateGameMap(std::vector<std::pair<std::vector<glm::vec2>, Stand>>& stands_with_nodes, std::vector<std::pair<std::vector<Transform>, std::string>>& map_sprites) {
	// for every stand (vector of its node-positions)
	for (auto& node : stands_with_nodes) {

		Stand s = node.second;

		// for every node-position in that stand
		for (auto& pos : node.first) {
			// create a node belonging to the stand with the desired position
			CreateNode(pos, s);
		}
	}
	
	for (auto& pair : map_sprites) {
		for (auto& sprite: pair.first) {
			GameObject* sp = new GameObject("map_sprite", sprite);
			sp->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture(pair.second), 1.0f, Geometry::RECTANGLE));
			this->AddGameObjectToLayer(sp);
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
	Layer* layer = this;
	GameObject* building = new GameObject(type + "-building", transform);

	if (type == "medic") {
		building->AddTag("medic_building");
		building->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Buildings/med_tent.png"), 1.0f, Geometry::RECTANGLE));
	}
	else if (type == "engineer") {
		building->AddTag("engineer_building");

		building->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Buildings/engineer_tent.png"), 1.0f, Geometry::RECTANGLE));
	}
	else {
		LOG_WARN("WARNING: probably no existing type given when creating a building");
	}
	building->onlyLayerReceive = true;
	AddGameObjectToLayer(building);

	return building;
}

bool MapLayer::GameObjectPressed(GameObjectPressedEvent& e) {
	// check if e belongs to allylayer - otherwise return false

	GameObject* clicked_mapobject = e.GetGameObject();

	if (clicked_mapobject == gameScene->GetActiveBuilding()) {
		gameScene->uiLayer->DeactivateBuildingUI();
		gameScene->SetActiveBuilding(nullptr);
		return true;
	}
	else {
		gameScene->uiLayer->DeactivateBuildingUI();
	}

	if (clicked_mapobject->HasTag("move_node")) {
		if (gameScene->GetActiveCharacter() == nullptr || !gameScene->GetActiveCharacter()->HasTag("soldier") || clicked_mapobject->GetComponent<Node>()->is_occupied) return false;

		gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->SoldierMove(clicked_mapobject);
		return true;
	}
	else if (clicked_mapobject->HasTag("medic_building")) {
		gameScene->uiLayer->ActivateMedicBuildlingUI();
	}
	else if (clicked_mapobject->HasTag("engineer_building")) {
		gameScene->uiLayer->ActivateEngineerBuildingUI();
	}
	else {
		return false;
	}

	gameScene->SetActiveBuilding(clicked_mapobject);

	return true;

}
