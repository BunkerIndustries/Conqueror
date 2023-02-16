#pragma once
#include "layers/ForegroundLayer.h"
#include "layers/BackgroundLayer.h"
#include "layers/SoundLayer.h"

// layers
inline ForegroundLayer* foreground_layer = new ForegroundLayer();
inline BackgroundLayer* background_layer = new BackgroundLayer();
inline SoundLayer* sound_layer = new SoundLayer();

// camera movement constants
inline float cameraScrollSpeed = 15.0f;
inline float cameraMoveSpeed = 2.0f;
inline float minCameraZPos = 2.0f;
inline float maxCameraZPos = 10.0f;

// all sprite paths
inline std::string soldier_sprite_path = "";
inline std::string medic_sprite_path = "";
inline std::string engineer_sprite_path = "";

// enemy grid constants
inline int enemy_grid_x = 5;
inline int enemy_grid_y = 3;
inline float enemy_grid_offset = 2.0f;
inline glm::vec2 enemy_grid_startpos = glm::vec2(0.0f, 0.0f);

// character constants
inline glm::vec2 character_scale = glm::vec2(0.9f, 1.2f);

// soldier constants
inline float soldier_movement_speed = 1.2f;
inline float medic_movement_speed = 1.4f;
inline float engineer_movement_speed = 0.9f;