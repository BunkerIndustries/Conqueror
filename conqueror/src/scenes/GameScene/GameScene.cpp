#include "_Game.h"
#include "GameScene.h"

#include "required/constants.h"

#include "utils/Engineer.h"
#include "utils/Supply.h"

GameScene::GameScene() {
	// set background color
	backcolor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	backgroundLayer = new BackgroundLayer();
	mapLayer = new MapLayer();
	enemyLayer = new EnemyLayer();
	allyLayer = new AllyLayer;
	uiLayer = new UILayer();

	waveManager = new WaveManager(this);
}

GameScene::~GameScene() {

}

void GameScene::OnStop() {
	RemoveLayer(backgroundLayer);
	RemoveLayer(mapLayer);
	RemoveLayer(enemyLayer);
	RemoveLayer(allyLayer);

	RemoveOverlay(uiLayer);
}
void GameScene::OnStart() {

	Supply::Init();

	AddLayer(backgroundLayer);
	AddLayer(mapLayer);
	AddLayer(enemyLayer);
	AddLayer(allyLayer);

	AddOverlay(uiLayer);
}

extern float con;

void GameScene::OnUpdate() {
	CameraMovement(Application::GetDT());
	waveManager->OnUpdate();
}

void UpdateCamera(Shr<Camera> camera, float moveX, float moveY, float zoom)
{
	// Update camera position and zoom level
	camera->position.x += moveX;
	camera->position.y += moveY;
	camera->position.z += zoom;

	// Clamp camera position within the box
	camera->position.x = std::clamp(camera->position.x, min_camera_positions.x, max_camera_positions.x);
	camera->position.y = std::clamp(camera->position.y, min_camera_positions.y, max_camera_positions.y);

	// Calculate the visible area based on the camera zoom
	float visibleWidth = (max_camera_positions.x - min_camera_positions.x) / camera->position.z;
	float visibleHeight = (max_camera_positions.y - min_camera_positions.y) / camera->position.z;

	// Calculate the maximum allowed camera position to prevent going outside the box
	float maxCameraX = max_camera_positions.x - (visibleWidth / 2.0f);
	float maxCameraY = max_camera_positions.y - (visibleHeight / 2.0f);

	// Adjust camera position if it goes outside the box when zoomed out
	camera->position.x = std::min(camera->position.x, maxCameraX);
	camera->position.y = std::min(camera->position.y, maxCameraY);

	// Clamp camera zoom level
	camera->position.z = std::clamp(camera->position.z, min_camera_z_pos, max_camera_z_pos);
}

void GameScene::CameraMovement(float dt)
{
	float speed = camera_move_speed;
	if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
	{
		speed *= camera_move_speed_multiplier;
	}
	if (Input::IsKeyPressed(KEY_S))
		UpdateCamera(camera, 0, -speed * dt, 0);
	if (Input::IsKeyPressed(KEY_W))
		UpdateCamera(camera, 0, speed * dt, 0);
	if (Input::IsKeyPressed(KEY_D))
		UpdateCamera(camera, speed * dt, 0, 0);
	if (Input::IsKeyPressed(KEY_A))
		UpdateCamera(camera, -speed * dt, 0, 0);
}

bool GameScene::OnMouseScroll(MouseScrolledEvent& e)
{
	UpdateCamera(camera, 0, 0, camera_scroll_speed * Application::GetDT() * e.GetYOffset());

	return true;
}

bool GameScene::GameObjectPressed(GameObjectPressedEvent& e) {

	return true;
}

bool GameScene::KeyPressed(KeyPressedEvent& e)
{
	if (e.getKeyCode() == KEY_ESCAPE)
	{
		delete menuScene;
		menuScene = new MenuScene();
		Application::ChangeScene(menuScene);
	}
	return false;
}

GameObject* GameScene::CreateBullet(Layer* layer, GameObject* target, glm::vec2 startPos, glm::vec2 targetPos) {
	GameObject* bullet = new GameObject("bullet", Transform(startPos, bullet_scale));
	bullet->AddComponent(new CircleRenderer(bullet_color, 1.0f, 0.005));
	bullet->AddComponent(new Movement(bullet_speed, targetPos));
	bullet->AddComponent(new BulletComponent(target, targetPos));
	bullet->AddTag("bullet");
	layer->AddGameObjectToLayer(bullet);
	return bullet;
}
