#ifdef _DEBUG
#pragma once  
#include "ColourDetection.h"  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include <GL/glew.h>

void GetTexFromVision(GLuint& textureID,const int& resizeTo)
{
	// imgMain is the main Mat image captured and processed by the vision system.
	if (vision::imgMain.empty()) return;  
	
	cv::Mat imgProcessed;
	cv::resize(vision::imgMain, imgProcessed, cv::Size(resizeTo, resizeTo));
	cv::cvtColor(imgProcessed, imgProcessed, cv::COLOR_BGR2RGB);

	if (textureID == 0) {
		// Generate a new texture ID if it doesn't exist
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// set scaling to linear (instead of nearest neighbour)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// set wrapping to clamp to edge (no repeat)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgProcessed.cols, imgProcessed.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, imgProcessed.data);
	} 
	else {
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	
	// needed for sorting the pixels correctly. otherwhise Mat data is not aligned to 4 byte boundaries
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Update texture content
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imgProcessed.cols, imgProcessed.rows, GL_RGB, GL_UNSIGNED_BYTE, imgProcessed.data);
	
	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
}
#endif