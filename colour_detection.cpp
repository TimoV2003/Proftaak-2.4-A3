#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <optional>

namespace vision {
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

	
	std::pair<std::vector<cv::Point>, cv::Rect> getBiggestContourByArea(cv::Mat image, int minimumArea) {
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;

		cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		std::vector<std::vector<cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		int biggestArea = 0;
		std::vector<cv::Point> biggestContour;
		cv::Rect rectOfBiggestContour;
		for (int i = 0; i < contours.size(); i++) {
			int area = cv::contourArea(contours[i]);

			if ((area > minimumArea) && (area > biggestArea)) {
				float peri = cv::arcLength(contours[i], true);
				cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
				boundRect[i] = cv::boundingRect(conPoly[i]);
				cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255, 255, 255), 2);
				biggestContour = contours[i];
				rectOfBiggestContour = boundRect[i];
				biggestArea = area;
			}
		}
		if (biggestArea == 0) {
			return {};
		}
		return {biggestContour, rectOfBiggestContour};
	}

	cv::Point getCentreOfContour(std::pair<std::vector<cv::Point>, cv::Rect> contour) {
		cv::Point centre(0, 0);
		centre.x = contour.second.x + contour.second.width / 2;
		centre.y = contour.second.y + contour.second.height / 2;
		return centre;
	}

	std::vector<cv::Mat> extractColor(cv::Mat image) {

		cv::Mat imgHSV;
		cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);
		std::vector<cv::Mat> masks(myColors.size());

		for (int i = 0; i < myColors.size(); i++) {
			cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
			cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
			cv::Mat mask;

			cv::inRange(imgHSV, lower, upper, masks[i]);
		}
		return masks;
	}

	int color_detection_loop() {
		while (true) {
			getContours(img);
			cap.read(img);
			auto masks = extractColor(img);
			for (cv::Mat mask : masks) {
				cv::Point centre;
				centre = getCentreOfContour(getBiggestContourByArea(mask, 1000));
				std::cout << centre.x << " " << centre.y << std::endl;
			}
			cv::imshow("Image", img);
			if (cv::waitKey(1) == 27) { break; }
		}
		return 0;
	}
}