#include "_Game.h"
#include "BackgroundLayer.h"
#include "required/constants.h"

BackgroundLayer::BackgroundLayer() {

}

void BackgroundLayer::OnAttach() {
	GameObject* background = new GameObject("background", Transform(glm::vec2(0.0f, 0.0f), background_image_size), ProjectionMode::PERSPECTIVE);
	background->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), DataPool::GetTexture("Map/fullscreen_dirtground.png"), Geometry::RECTANGLE));
	this->AddGameObjectToLayer(background);
}
