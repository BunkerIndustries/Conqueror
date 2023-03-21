#pragma once
#include "_Core.h"

#include "utility.h"

namespace core {
	namespace Utils
	{
        std::string GetSystemDateInString();
        std::string GetSystemTimeInString();
        // random function
		float randRange(int min, int max);

        struct Size {
            float width;
            float height;
        };
		Size CalculateAspectRatioFit(float srcWidth, float srcHeight, float maxWidth, float maxHeight);

	}
}