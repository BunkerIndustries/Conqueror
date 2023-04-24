#include "_Game.h"
#include "BackgroundLayer.h"
#include "required/constants.h"

BackgroundLayer::BackgroundLayer() {

}

void BackgroundLayer::OnAttach() {
	glm::vec2 background_tile_rad = background_tile_size / 2.0f;
	CreateBackgroundTile(glm::vec2(-background_tile_rad.x, background_tile_rad.y));
	CreateBackgroundTile(glm::vec2(background_tile_rad.x, background_tile_rad.y));
	CreateBackgroundTile(glm::vec2(-background_tile_rad.x, -background_tile_rad.y));
	CreateBackgroundTile(glm::vec2(background_tile_rad.x, -background_tile_rad.y));
}

void BackgroundLayer::CreateBackgroundTile(glm::vec2 pos) {
	GameObject* tile = new GameObject("background-tile", Transform(pos, background_tile_size), ProjectionMode::PERSPECTIVE);
	tile->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Map/fullscreen_dirtground.png"), 1.0f, Geometry::RECTANGLE));
	this->AddGameObjectToLayer(tile);
}
