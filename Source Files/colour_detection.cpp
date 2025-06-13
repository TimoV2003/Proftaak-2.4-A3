#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <atomic>

namespace vision {
	//first element is the contour, second element is the bounding rectangle of the contour
	typedef std::pair<std::vector<cv::Point>, cv::Rect> ContourWithBoundingRect;

	float visionNormalisedPosition = 0;
	std::mutex visionPositionMutex;

	cv::Mat img;
	cv::VideoCapture cap(0);

	std::vector<std::vector<int>> myColors{ {0, 0, 0, 180, 255, 50} };
	std::vector<cv::Scalar> myColorValues{ {255, 255, 255} };

	//deprecated: Use other specialised functions instead
	cv::Point getContours(cv::Mat image) {
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;

		cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		std::vector<std::vector<cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		cv::Point myPoint(0, 0);

		for (int i = 0; i < contours.size(); i++) {
			int area = cv::contourArea(contours[i]);

			if (area > 1000) {
				float peri = cv::arcLength(contours[i], true);
				cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
				boundRect[i] = cv::boundingRect(conPoly[i]);

				myPoint.x = boundRect[i].x + boundRect[i].width / 2;
				myPoint.y = boundRect[i].y + boundRect[i].height / 2;

				cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255, 255, 255), 2);
			}
		}
		return myPoint;
	}
	
	ContourWithBoundingRect getBiggestContourByArea(cv::Mat image, int minimumArea) {
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;

		cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		std::vector<std::vector<cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		int biggestArea = 0;
		int biggestContourIteration = 0;
		std::vector<cv::Point> biggestContour;
		cv::Rect rectOfBiggestContour;
		for (int i = 0; i < contours.size(); i++) {
			int area = cv::contourArea(contours[i]);

			if ((area > minimumArea) && (area > biggestArea)) {
				biggestArea = area;
				biggestContourIteration = i;
			}
		}
		if (biggestArea == 0) {
			return {};
		}
		float peri = cv::arcLength(contours[biggestContourIteration], true);
		cv::approxPolyDP(contours[biggestContourIteration], conPoly[biggestContourIteration], 0.02 * peri, true);
		boundRect[biggestContourIteration] = cv::boundingRect(conPoly[biggestContourIteration]);
		biggestContour = contours[biggestContourIteration];
		rectOfBiggestContour = boundRect[biggestContourIteration];
		return {biggestContour, rectOfBiggestContour};
	}

	/*x value is horizontal where 0 is right (on camera)
	* y value is vertical where 0 is top (on camera)*/
	cv::Point getCentreOfContour(ContourWithBoundingRect contour) {
		cv::Point centre(0, 0);
		centre.x = contour.second.x + contour.second.width / 2;
		centre.y = contour.second.y + contour.second.height / 2;
		return centre;
	}

	void drawContour(ContourWithBoundingRect contour) {
		cv::rectangle(img, contour.second.tl(), contour.second.br(), cv::Scalar(255, 255, 255), 2);
	}

	cv::Mat extractColor(cv::Mat image, std::vector<int> color) {

		cv::Mat imgHSV;
		cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);
		cv::Mat mask;


		cv::Scalar lower(color[0], color[1], color[2]);
		cv::Scalar upper(color[3], color[4], color[5]);

		cv::inRange(imgHSV, lower, upper, mask);
		return mask;
	}

	void color_detection_loop(std::atomic<bool>& shouldStop) {
		while (!shouldStop) {
			cap.read(img);
			auto mask = extractColor(img, myColors[0]);
			auto biggestContour = getBiggestContourByArea(mask, 1000);
			if (!biggestContour.first.empty()) {
				cv::Point centreOfBiggestContour;
				centreOfBiggestContour = getCentreOfContour(biggestContour);
				int widthOfImage = img.cols;
				{
					std::lock_guard<std::mutex> lock(visionPositionMutex);
					visionNormalisedPosition = centreOfBiggestContour.x / (float)widthOfImage;
				}
				drawContour(biggestContour);
			}

			cv::imshow("Image", img);
			if (cv::waitKey(1) == 27) { break; }
		}
	}
}