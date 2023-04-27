#include "_Game.h"

#include "EnemyLayer.h"
#include "required/constants.h"
#include "required/functions.h"

EnemyLayer::EnemyLayer()
	: Layer("EnemyLayer")
{

}

EnemyLayer::~EnemyLayer()
{

}

void EnemyLayer::OnAttach()
{
}

void EnemyLayer::OnDetach()
{

}

void EnemyLayer::Update(const float dt)
{

}

void EnemyLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<KeyPressedEvent>([this](KeyPressedEvent& e)
	{
		if (e.getKeyCode() == KEY_G)
		{
			CreateEnemy("enemy", glm::vec2(RandomF(enemy_grid_startpos.x - enemy_spawn_random_x_radius, enemy_grid_startpos.x + enemy_spawn_random_x_radius), enemy_spawn_y_position));
			return true;
		}
	return false;
	});

}

GameObject* EnemyLayer::CreateEnemy(std::string name, glm::vec2 spawn_pos) {
	GameObject* enemy_go = new GameObject(name, Transform(spawn_pos, enemy_scale));

	enemy_go->AddTag("enemy");
	enemy_go->AddComponent(new SpriteRenderer(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Geometry::RECTANGLE));		// TODO: Change to sprite_path
	enemy_go->AddComponent(new Movement(enemy_movement_speed));
	enemy_go->AddComponent(new EnemyBehaviour());
	enemy_go->AddComponent(new EnemyShooting());
	enemy_go->AddComponent(new Health(enemy_health));

	AddGameObjectToLayer(enemy_go);

	return enemy_go;
}
