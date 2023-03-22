#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define GLFW_INCLUDE_NONE

//C++ Libraries
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <map>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <time.h>
#include <list>
#include <cmath>
#include <thread>
#include <algorithm>
#include <functional>
#include <random>

//C Libraries
#include <stdio.h>
#include <string.h>
#include <dirent/include/dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

//GLM
//glm itself
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
//vectors
#include <GLM/vector_relational.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
//matrixes
#include <GLM/matrix.hpp>
#include <GLM/mat2x2.hpp>
#include <GLM/mat2x3.hpp>
#include <GLM/mat2x4.hpp>
#include <GLM/mat3x2.hpp>
#include <GLM/mat3x3.hpp>
#include <GLM/mat3x4.hpp>
#include <GLM/mat4x2.hpp>
#include <GLM/mat4x3.hpp>
#include <GLM/mat4x4.hpp>


//Core
#include "Engine.h"

//components
#include "required/components.h"


#ifdef CORE_PLATFORM_WINDOWS
#include <Windows.h>
#endif