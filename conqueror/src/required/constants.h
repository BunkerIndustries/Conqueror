#pragma once
#include "layers/ForegroundLayer.h"
#include "layers/SoundLayer.h"
#include "components/medic_management.h"

// TODO: May split this up to multiple files, so that not everything has to be inline

// layers
inline ForegroundLayer* foreground_layer = new ForegroundLayer();
inline SoundLayer* sound_layer = new SoundLayer();

// enemy movement grid
inline std::vector<std::vector<GameObject*>> enemy_grid;

// camera movement constants
inline float cameraScrollSpeed = 15.0f;
inline float cameraMoveSpeed = 2.0f;
inline float minCameraZPos = 2.0f;
inline float maxCameraZPos = 20.0f;

// all sprite paths
inline std::string soldier_sprite_path = "";
inline std::string medic_sprite_path = "";
inline std::string engineer_sprite_path = "";
inline std::string enemy_sprite_path = "";

// enemy grid constants
inline const int enemy_grid_x = 10;
inline const int enemy_grid_y = 6;
inline float enemy_grid_offset = 0.5f;
inline glm::vec2 enemy_grid_startpos = glm::vec2(0.0f, 2.0f);

// enemy behaviour constants
inline float min_enemy_waiting_time = 0.5f;
inline float max_enemy_waiting_time = 2.0f;
inline float enemy_movement_speed = 1.0f;
inline uint8_t max_enemy_lock_target_tries = 3;
inline glm::vec2 enemy_scale = glm::vec2(0.7f, 1.0f);
inline uint8_t enemy_random_movement_sum = 5;
inline uint8_t enemy_move_left_probability = 1;
inline uint8_t enemy_move_mid_probability = 3;
inline uint8_t enemy_move_right_probability = 1;

// character constants
inline float soldier_movement_speed = 1.2f;
inline float medic_movement_speed = 1.4f;
inline float engineer_movement_speed = 0.9f;
inline glm::vec2 character_scale = glm::vec2(0.9f, 1.2f);	// probably temporary

//soldier behaviour constants
inline float min_soldier_shoot_waiting_time = 0.5f;
inline float max_soldier_shoot_waiting_time = 1.5f;
inline uint8_t max_soldier_lock_target_tries = 2;
inline uint8_t soldier_miss_points = 1;

// stands constants (probabilities have to be choose_probability_sum in total)
inline uint8_t choose_probability_sum = 100;
inline uint8_t front_choose_probability = 45;
inline uint8_t mg_choose_probability = 20;
inline uint8_t trench_choose_probability = 15;
inline uint8_t hiding_choose_probability = 8;
inline uint8_t artillerie_choose_probability = 12;

// shooting constants
inline uint8_t max_hit_probability = 10;
inline uint8_t front_hit_probability = 8;
inline uint8_t mg_hit_probability = 6;
inline uint8_t trench_hit_probability = 5;
inline uint8_t hiding_hit_probability = 4;
inline uint8_t artillerie_hit_probability = 6;

// damage constants
inline uint8_t soldier_damage = 35;
inline uint8_t enemy_damage = 35;

// health constants
inline float enemy_health = 100.0f;
inline float soldier_health = 100.0f;
inline float medic_health = 50.0f;
inline float engineer_health = 200.0f;

// bullet constants
inline float bullet_speed = 30.0f;
inline glm::vec4 bullet_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
inline glm::vec2 bullet_size = glm::vec2(0.5f, 0.5f);
inline float min_inaccuracy = 0.8f;
inline float max_inaccuracy = 1.4f;

// node constants
inline glm::vec2 node_size = glm::vec2(0.5f, 0.5f);
inline float node_alpha = 0.8f;
inline glm::vec4 node_front_color = glm::vec4(0.9f, 0.0f, 0.0f, node_alpha);
inline glm::vec4 node_mg_color = glm::vec4(0.9f, 0.2f, 0.0f, node_alpha);
inline glm::vec4 node_trench_color = glm::vec4(0.9f, 0.0f, 0.0f, node_alpha);
inline glm::vec4 node_hiding_color = glm::vec4(0.5f, 0.0f, 0.5f, node_alpha);
inline glm::vec4 node_artillerie_color = glm::vec4(0.6f, 0.4f, 0.2f, node_alpha);
inline glm::vec4 node_bunker_color = glm::vec4(0.0f, 0.9f, 0.0f, node_alpha);
inline glm::vec4 node_waiting_color = glm::vec4(0.0f, 0.4f, 0.4f, node_alpha);

// time constants
inline float waiting_time_factor = 4.0f;

// medics constants
inline uint8_t medic_count = 15;
inline MedicManagement* medic_management = new MedicManagement(medic_count);