#pragma once
#include <opencv2/core/types.hpp>
#include <mutex>

namespace vision {
	void color_detection_loop(std::atomic<bool>& shouldStop);
	extern float visionNormalisedPosition;
	extern std::mutex visionPositionMutex;
	extern cv::Mat imgMain;
}