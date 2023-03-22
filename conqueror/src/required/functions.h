#pragma once
#include "_Game.h"

inline void RoundVec2(glm::vec2& vec) {		// written by chatGPT 0_0
	// rounds to 2 decimal places
	vec.x = std::roundf(vec.x * powf(10, 2)) / powf(10, 2);	
	vec.y = std::roundf(vec.y * powf(10, 2)) / powf(10, 2);
	
}

inline int RandomInt(const int from, const int to) {	// written by chatGPT 0_0
	
	std::random_device rd;  // Use a true random number source
	std::mt19937 generator(rd());  // Use Mersenne Twister algorithm
	std::uniform_int_distribution<> distribution(from, to);  // Distribute numbers evenly

	return distribution(generator);  // Generate the random number and return it
}

inline float RandomF(float min_float, float max_float) {	// written by chatGPT 0_0
	static bool initialized = false;
	if (!initialized) {
		srand(time(nullptr)); // set seed based on current time, only once
		initialized = true;
	}
	float random = ((float)rand()) / (float)RAND_MAX; // generate random float between 0 and 1
	float range = max_float - min_float; // calculate range
	return (random * range) + min_float; // scale and shift the random number to the desired range
}

inline int SumTo(int n) {
	return n * (n + 1) / 2;
}
