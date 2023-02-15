#pragma once
#include "_Core.h"

#include "utility.h"

namespace core {
	namespace Utils
	{
        std::string getSystemDateInString();
        std::string getSystemTimeInString();
        // random function
		float randRange(int min, int max);

        struct Size {
            float width;
            float height;
        };
		Size calculateAspectRatioFit(float srcWidth, float srcHeight, float maxWidth, float maxHeight);

	}
}