#pragma once

// camera movement constants
inline float cameraScrollSpeed = 15.0f;
inline float cameraMoveSpeed = 2.0f;
inline float minCameraZPos = 2.0f;
inline float maxCameraZPos = 10.0f;

// enemy grid constants
inline int enemy_grid_x = 5;
inline int enemy_grid_y = 3;
inline float enemy_grid_offset = 2.0f;
inline glm::vec2 enemy_grid_startpos = glm::vec2(0.0f, 0.0f);