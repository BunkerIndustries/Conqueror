#include "_Game.h"
#include "BackgroundLayer.h"
#include "required/constants.h"

BackgroundLayer::BackgroundLayer() {
}

void BackgroundLayer::Load()
{
	CreateBackgroundTile(glm::vec2(0, 0));
}

void BackgroundLayer::OnAttach() {
}

void BackgroundLayer::CreateBackgroundTile(glm::vec2 pos) {
	GameObject* tile = new GameObject("background-tile", Transform(pos, background_tile_size), ProjectionMode::PERSPECTIVE);
	tile->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Map/dirt_pattern.png"), 100.0f, Geometry::RECTANGLE));
	this->AddGameObjectToLayer(tile);
}
