#include "test.h"

testScene::testScene() {

}

void testScene::loadResources() {

}

void testScene::init() {

}

void testScene::update(float dt) {
	if (Input::IsKeyPressed(KEY_D)) {
		camera->position.x += 5;
	}

	this->renderer->render(Application::GetLayerStack(), dt);
}

bool testScene::OnMouseScroll(MouseScrolledEvent& e) {
	return true;
}

bool testScene::OnMouseClick(MouseButtonPressedEvent& e) {
	return true;
}