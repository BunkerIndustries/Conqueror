#include "_Game.h"
#include "MenuBackgroundLayer.h"
#include "required/constants.h"

MenuBackgroundLayer::MenuBackgroundLayer() {
}

void MenuBackgroundLayer::OnAttach() {
	CreateBackgroundTile(glm::vec2(0, 0));
}

void MenuBackgroundLayer::CreateBackgroundTile(glm::vec2 pos) {
	GameObject* tile = new GameObject("background-tile", Transform(pos, background_tile_size, 45.0f), ProjectionMode::PERSPECTIVE);
	tile->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("bunker_floor.png"), 100.0f, Geometry::RECTANGLE));
	this->AddGameObjectToLayer(tile);
}