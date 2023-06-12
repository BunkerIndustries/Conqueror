#include "_Game.h"

#include "MapLayer.h"
#include "components/DestroyOverTime.h"
#include "components/SingleAnimationComponent.h"

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
	medicBuilding = Medic::AddBuilding(Transform(glm::vec2(11.0f, -11.5f), building_size), start_medic_stock);
	engineerBuilding = Engineer::AddBuilding(Transform(glm::vec2(-11.0f, -11.5f), building_size), start_engineer_stock);
}

void MapLayer::OnDetach()
{
}

void MapLayer::Update(const float dt)
{
}

GameObject* MapLayer::CreateNode(glm::vec2 position, Stand& node_stand) {

	glm::vec2 node_scale = glm::vec2(node_size);
	std::string sprite_path = "node_placeholder.png";

	GameObject* node_go = new GameObject("node", Transform(position, node_scale));
	node_go->AddComponent(new Node(node_stand.stand));

	node_go->AddTag("move_node");

	// TODO: change sprite_path and node_scale each
	if (node_stand.stand == waiting_stand.stand) {
		waiting_nodes.push_back(node_go);
		node_go->RemoveTag("move_node");
		sprite_path = "spawn_point.png";
		node_scale = waiting_node_size;
	}
	else if (node_stand.stand == trench_stand.stand) {
		trench_nodes.push_back(node_go);
		sprite_path = "Map/bunker_tiles_top.png";
		node_scale = trench_node_size;
	}
	else if (node_stand.stand == mg_stand.stand) {
		sprite_path = "Map/bunker_tiles_top.png";
		node_scale = trench_node_size;
	}
	else if (node_stand.stand == artillerie_stand.stand) {
		sprite_path = "Map/action_spot_hay.png";
		node_scale = artillery_node_size;
	}
	else if (node_stand.stand == bunker_stand.stand) {
		sprite_path = "bunker_floor.png";
		node_scale = bunker_node_size;
	}
	else if (node_stand.stand == hiding_stand.stand) {
		hiding_nodes.push_back(node_go);
		CreateMapSprite("Map/walls_frontview.png", Transform(position + hiding_sprite_node_offset, hiding_sprite_size));
		sprite_path = "Map/action_spot_hay.png";
		node_scale = hiding_node_size;
	}
	else if (node_stand.stand == front_stand.stand) {
		sprite_path = "action_spot_hay.png";
	}

	node_go->AddComponent(new SpriteRenderer(white_color, DataPool::GetTexture(sprite_path), 1.0f, Geometry::RECTANGLE));
	node_go->transform.scale = node_scale;

	node_go->onlyLayerReceive = true;
	AddGameObjectToLayer(node_go);

	return node_go;
}

void MapLayer::RotateTrenchNodes() {
	for (size_t i = 0; i < 7; i++) {
		trench_nodes.at(i)->transform.rotation = 45.0f;
	}
	for (size_t i = trench_nodes.size()-7; i < trench_nodes.size() ; i++) {
		trench_nodes.at(i)->transform.rotation = -45.0f;
	}
}

void MapLayer::CreateDeadBody(std::string sprite_path, glm::vec2 position) {
	GameObject* sp = new GameObject("map_sprite", Transform(position, dead_body_size));
	sp->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture(sprite_path), 1.0f, Geometry::RECTANGLE));
	sp->AddComponent(new DestroyOverTime(dead_body_lasting_time));
	this->AddGameObjectToLayer(sp);
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

	RotateTrenchNodes();
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

			y_row.at(y)->AddComponent(new SpriteRenderer(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), Geometry::RECTANGLE));	// add SpriteRenderer
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

GameObject* MapLayer::CreateMg(glm::vec2 mg_position, GameObject* mg_node) {

	GameObject* mg = new GameObject("mg", Transform(mg_position, mg_size));
	mg->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Buildings/mg_stand.png"), 80.0f, 224.0f, 0.0f, 0.0f, glm::vec2(0, 0)));
	mg->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(0, 0));
	mg->AddComponent(new SingleAnimation(DataPool::GetTexture("Anims/mg_animation.png"), 104.0f, 296.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 0.0f), 10, glm::vec2(0.0f, 0.0f), DataPool::GetTexture("Anims/mg_animation.png"), 104.0f, 296.0f, 16.0f, 16.0f));
	mg->AddComponent(new MgComponent(mg_node));
	AddGameObjectToLayer(mg);

	return mg;
}

GameObject* MapLayer::CreateArtillery(glm::vec2 artillery_position, GameObject* artillery_node) {

	GameObject* artillery = new GameObject("artillery", Transform(artillery_position, artillery_size));
	artillery->AddComponent(new SpriteSheet(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Buildings/artillerie_front_north.png"), 248.0f, 400.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f)));
	artillery->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(0.0f, 0.0f));
	artillery->AddComponent(new ArtilleryComponent(artillery_node));

	artillery->AddComponent(new SingleAnimation(DataPool::GetTexture("Buildings/artillerie_front_north.png"), 248.0f, 400.0f, 16.0f, 16.0f, glm::vec2(0.0f, 0.0f), glm::vec2(2.0f, 0.0f), artillery_shoot_anim_speed, glm::vec2(0.0f, 0.0f), DataPool::GetTexture("Buildings/artillerie_front_north.png"), 248.0f, 400.0f, 16.0f, 16.0f));

	AddGameObjectToLayer(artillery);
	return artillery;
}

bool MapLayer::GameObjectPressed(GameObjectPressedEvent& e) {
	// check if e belongs to allylayer - otherwise return false

	GameObject* clicked_mapobject = e.GetGameObject();

	if (clicked_mapobject == gameScene->GetActiveBuilding()) {
		gameScene->uiLayer->DeactivateBuildingUI();
		gameScene->SetActiveBuilding(nullptr);
		return true;
	}

	if (clicked_mapobject->HasTag("move_node")) {
		if (gameScene->GetActiveCharacter() == nullptr || !gameScene->GetActiveCharacter()->HasTag("soldier") || clicked_mapobject->GetComponent<Node>()->is_occupied) return false;

		gameScene->GetActiveCharacter()->GetComponent<SoldierBehaviour>()->SoldierMove(clicked_mapobject);
		return true;
	}
	else if (clicked_mapobject->HasTag("medic_building")) {
		gameScene->uiLayer->DeactivateBuildingUI();
		gameScene->uiLayer->ActivateMedicBuildlingUI();
	}
	else if (clicked_mapobject->HasTag("engineer_building")) {
		gameScene->uiLayer->DeactivateBuildingUI();
		gameScene->uiLayer->ActivateEngineerBuildingUI();
	}
	else {
		return false;
	}

	gameScene->SetActiveBuilding(clicked_mapobject);

	return true;

}
