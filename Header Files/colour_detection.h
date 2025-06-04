#pragma once
#include <opencv2/core/types.hpp>
#include <mutex>

namespace vision {
	void color_detection_loop(std::atomic<bool>& shouldStop);
	extern cv::Point visionPosition;
	extern std::mutex visionPositionMutex;
}