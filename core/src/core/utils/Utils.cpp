#include "_Core.h"

#include "utils/Utils.h"

namespace core {
    namespace Utils {
        std::string Utils::getSystemDateInString() {
            std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            char buf[26];
            ctime_s(buf, sizeof(buf), &end_time);
            return std::string(buf);
        }

        std::string Utils::getSystemTimeInString() {
            time_t now = time(0);
            struct tm tstruct;
            localtime_s(&tstruct, &now);
            char buf[80];
            // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
            // for more information about date/time format
            strftime(buf, sizeof(buf), "%X", &tstruct);

            return std::string(buf);
        }

        float Utils::randRange(int min, int max)
        {
            int diff = max - min;
            // stackoverflow magic
            return (((double)(diff + 1) / RAND_MAX) * rand() + min); // math is powerful(!!)
        }

        Size Utils::calculateAspectRatioFit(float srcWidth, float srcHeight, float maxWidth, float maxHeight) {

            float ratio = fmin(maxWidth / srcWidth, maxHeight / srcHeight);
            Size xy;
            xy.width = srcWidth * ratio;
            xy.height = srcHeight * ratio;
            return xy;
        }
    }
}