#pragma once
#include "scenes/MenuScene/MenuScene.h"
#include "scenes/GameScene/GameScene.h"

// scenes
inline GameScene* gameScene;
inline MenuScene* menuScene;

// enemy movement grid
inline std::vector<std::vector<GameObject*>> enemy_grid;

// camera movement 
inline float camera_scroll_speed = 28.0f;
inline float camera_move_speed = 2.0f;
inline float min_camera_z_pos = 2.0f;
inline float max_camera_z_pos = 15.0f;
inline glm::vec2 min_camera_positions = glm::vec2(-7.0f, -5.0f);
inline glm::vec2 max_camera_positions = glm::vec2(7.0f, 3.0f);

// enemy grid 
inline const int enemy_grid_x = 15;
inline const int enemy_grid_y = 9;
inline float enemy_grid_offset = 1.0f;
inline glm::vec2 enemy_grid_startpos = glm::vec2(0.0f, 5.0f);

// enemy behaviour 
inline float min_enemy_waiting_time = 0.5f;
inline float max_enemy_waiting_time = 2.0f;
inline float enemy_movement_speed = 1.0f;
inline uint8_t max_enemy_lock_target_tries = 3;
inline glm::vec2 enemy_scale = glm::vec2(0.7f, 1.0f);
inline uint8_t enemy_random_movement_sum = 5;
inline uint8_t enemy_move_left_probability = 1;
inline uint8_t enemy_move_mid_probability = 3;
inline uint8_t enemy_move_right_probability = 1;
inline float enemy_spawn_y_position = 15.0f;
inline float enemy_spawn_random_x_radius = 5.0f;

// character 
inline float soldier_movement_speed = 1.2f;
inline float medic_movement_speed = 1.4f;
inline float engineer_movement_speed = 3.9f;
inline glm::vec2 character_scale = glm::vec2(0.9f, 1.2f);	// probably temporary

//bullet
inline float bullet_speed = 20.0f;
inline glm::vec2 bullet_scale = glm::vec2(0.5f, 1.0f);	// probably temporary

//soldier behaviour 
inline float min_soldier_shoot_waiting_time = 0.7f;
inline float max_soldier_shoot_waiting_time = 1.0f;
inline uint8_t max_soldier_lock_target_tries = 2;
inline uint8_t soldier_miss_points = 1;
inline glm::vec2 soldier_spawn_pos = glm::vec2(-5.0f, -10.0f);

// stands (probabilities have to be choose_probability_sum in total)
inline uint8_t choose_probability_sum = 100;
inline uint8_t front_choose_probability = 45;
inline uint8_t mg_choose_probability = 20;
inline uint8_t trench_choose_probability = 15;
inline uint8_t hiding_choose_probability = 8;
inline uint8_t artillerie_choose_probability = 12;

// shooting 
inline uint8_t max_hit_probability = 10;
inline uint8_t front_hit_probability = 8;
inline uint8_t mg_hit_probability = 6;
inline uint8_t trench_hit_probability = 5;
inline uint8_t hiding_hit_probability = 4;
inline uint8_t artillerie_hit_probability = 6;

// damage 
inline uint8_t soldier_damage = 35;
inline uint8_t enemy_damage = 35;

// health 
inline float enemy_health = 100.0f;
inline float soldier_health = 100.0f;
inline float medic_health = 50.0f;
inline float engineer_health = 200.0f;

// bullet trace 
inline glm::vec4 trace_color = glm::vec4(1.0f, 0.0f, 0.0f, 0.8f);
inline float min_inaccuracy = 0.8f;
inline float max_inaccuracy = 1.4f;
inline float trace_thickness = 0.3f;
inline float trace_lasting = 0.15f;
inline bool bulletDistanceMoreInaccuracy = true;
inline float bulletInaccuracyMultiplicator = 10.0f;

// node 
inline glm::vec2 node_size = glm::vec2(0.5f, 0.5f);
inline float node_alpha = 0.8f;
inline glm::vec4 node_front_color = glm::vec4(0.9f, 0.0f, 0.0f, node_alpha);
inline glm::vec4 node_mg_color = glm::vec4(0.9f, 0.2f, 0.0f, node_alpha);
inline glm::vec4 node_trench_color = glm::vec4(0.9f, 0.0f, 0.0f, node_alpha);
inline glm::vec4 node_hiding_color = glm::vec4(0.5f, 0.0f, 0.5f, node_alpha);
inline glm::vec4 node_artillerie_color = glm::vec4(0.6f, 0.4f, 0.2f, node_alpha);
inline glm::vec4 node_bunker_color = glm::vec4(0.0f, 0.9f, 0.0f, node_alpha);
inline glm::vec4 node_waiting_color = glm::vec4(0.0f, 0.4f, 0.4f, node_alpha);

// time 
inline float game_time_factor = 3.0f;

// medics 
inline glm::vec2 medic_healing_position_offset = glm::vec2(0.5f, 0.0f);
inline float waiting_time_per_hp = 0.03f;

// engineer 
inline glm::vec2 engineer_building_position_offset = glm::vec2(0.5f, 0.0f);
inline float building_time = 2.5f;

// buildings
inline glm::vec2 building_size = glm::vec2(3.0f, 3.0f);

// wave 
inline float start_preparation_time = 4.0f;
inline float start_wave_duration = 4.0f;
inline float wave_length_gradient = 1.5f;
inline float enemy_start_spawn_interval = 2.0f;
inline float enemy_spawn_interval_gradient = 0.9f;

// stocks
inline unsigned int start_soldier_stock = 5;
inline uint8_t start_engineer_stock = 3;
inline uint8_t start_medic_stock = 3;

// mg
inline glm::vec2 mg_size = glm::vec2(0.6f, 0.8f);
inline unsigned int mg_magazin_size = 50;
inline float mg_reload_time = 3.0f;
inline float mg_shoot_interval = 0.05f;
inline float mg_miss_points = 5;
inline float mg_damage = 15;
inline float mg_inaccuracy = 10.0f;
inline glm::vec2 mg_position_offset = glm::vec2(0.0f, 0.4f);

// artillery
inline glm::vec2 artillery_size = glm::vec2(0.7f, 0.9f); 
inline float artillery_min_reload_time = 0.5f;
inline float artillery_max_reload_time = 2.5f;
inline float artillery_normal_damage = 70.0f;
inline float artillery_critical_damage = 100.0f;
inline glm::vec2 artillery_explosion_size = glm::vec2(3.0f, 3.0f);
inline glm::vec2 artillery_position_offset = glm::vec2(0.0f, 0.4f);

// ui fonts
inline std::string ui_font_family = "PixeloidMono.ttf";
inline glm::vec4 ui_font_color = glm::vec4(1.0f, 1.0f, 1.0f, 0.8f);

// character ui color
inline glm::vec4 ui_character_background_color = glm::vec4(0.2f, 0.2f, 0.2f, 0.6f);
inline glm::vec4 ui_building_background_color = glm::vec4(0.15f, 0.15f, 0.15f, 0.6f);
inline glm::vec4 ui_header_color = glm::vec4(0.1f, 0.1f, 0.1f, 0.6f);
inline glm::vec4 ui_call_medic_button_color = glm::vec4(0.0f, 0.8f, 0.0f, 0.8f);
inline glm::vec4 ui_place_mg_button_color = glm::vec4(0.2f, 0.5f, 0.5f, 0.8f);
inline glm::vec4 ui_place_artillerie_button_color = glm::vec4(0.1f, 0.4f, 0.4f, 0.8f);

// character and building ui transform
inline glm::vec2 ui_building_background_size = glm::vec2(0.3f, 0.73f);
inline glm::vec2 ui_background_size = glm::vec2(0.3f, 0.6f);
inline glm::vec2 ui_character_position = glm::vec2(0.8f, 0.0f);
inline glm::vec2 ui_building_position = glm::vec2(-0.8f, 0.0f);
inline Transform ui_header_transform = Transform(glm::vec2(0.0f, 0.4f), glm::vec2(0.8f, 0.25f));
inline Transform ui_header_name_transform = Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.7f));
inline Transform ui_header_building_name_transform = Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.16f, 0.75f));
inline Transform ui_character_icon_transform = Transform(glm::vec2(0.0f, 1.0f), glm::vec2(0.3f, 0.32f));
inline Transform ui_building_icon_transform = Transform(glm::vec2(0.0f, 1.0f), glm::vec2(0.3f, 0.24f));
inline Transform ui_first_button_transform = Transform(glm::vec2(0.0f, -0.1f), glm::vec2(0.5f, 0.22f));
inline Transform ui_second_button_transform = Transform(glm::vec2(0.0f, -0.6f), glm::vec2(0.5f, 0.22f));
inline Transform ui_building_count_transform = Transform(glm::vec2(0.0f, 0.0f), glm::vec2(0.1, 0.1));

// supply menu ui color
inline glm::vec4 ui_supply_menu_background_color = glm::vec4(0.5f, 0.5f, 0.5f, 0.6f);
inline glm::vec4 ui_choice_field_color = glm::vec4(0.2f, 0.2f, 0.2f, 0.6f);
inline glm::vec4 ui_choice_field_button_color = glm::vec4(0.8f, 0.6f, 0.4f, 0.7f);

//supply menu ui transform
inline glm::vec2 ui_supply_menu_background_size = glm::vec2(1.5f, 1.44f);
inline Transform ui_supply_menu_text_transform = Transform(glm::vec2(0.0f, 0.8f), glm::vec2(0.04f, 0.105f));
inline Transform ui_supply_menu_text2_transform = Transform(glm::vec2(0.0f, 0.575f), glm::vec2(0.03f, 0.05f));
inline glm::vec2 ui_left_choice_field_position = glm::vec2(-0.45f, -0.18f);
inline glm::vec2 ui_right_choice_field_position = glm::vec2(0.45f, -0.18f);
inline glm::vec2 ui_choice_field_size = glm::vec2(0.32f, 0.58f);
inline Transform ui_choice_field_text_transform = Transform(glm::vec2(0.0f, 0.9f), glm::vec2(0.1f, 0.16f));
inline Transform ui_choice_field_count_transform = Transform(glm::vec2(0.0f, 0.5f), glm::vec2(0.11f, 0.14f));
inline Transform ui_choice_field_button_transform = Transform(glm::vec2(0.0f, -0.63f), glm::vec2(0.7f, 0.2f));

// supply menu
inline uint8_t min_soldiers_choice = 2;
inline uint8_t max_soldiers_choice = 5;
inline uint8_t soldier_increase_by_wave = 3;

// map sprites
inline glm::vec2 background_tile_size = glm::vec2(30.0f, 15.0f);
inline glm::vec2 hiding_sprite_size = glm::vec2(1.6f, 0.85f);
inline glm::vec2 hiding_sprite_node_offset = glm::vec2(0.0f, 0.8f);