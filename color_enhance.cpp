#pragma once

#include "stdafx.h"
#include "calc_bound.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void EnhanceColor(const Mat src_image, Mat& dest_image, float thresh_portion) {

	Mat src_image_hsv;
	cv::cvtColor(src_image, src_image_hsv, CV_BGR2HSV);
	vector<Mat> hsv_channels;
	cv::split(src_image_hsv, hsv_channels);

	const int num_bins = 256;
	const int num_pixels = src_image.rows * src_image.cols;
	const int histSize[] = { num_bins, num_pixels };
	const float range[] = { 0, 255 };
	const float* ranges[] = { range, range, range };
	const int channel_to_calc[] = { 0 };

	/**** S Channel *****/
	/*** Calculate current histogram ***/
	Mat hist;
	cv::calcHist(&hsv_channels[1], 1, channel_to_calc, Mat(),
		hist, 1, histSize, ranges,
		true, false);

	/*** Calculate current upper/lower bound ***/
	uchar lower_bound = CalcLowerBound(hist, num_pixels, thresh_portion);
	uchar higher_bound = CalcUpperBound(hist, num_pixels, thresh_portion);

	float scale_factor = (255.0 / (higher_bound - lower_bound));

	cv::subtract(hsv_channels[1], lower_bound, hsv_channels[1]);
	cv::multiply(hsv_channels[1], scale_factor, hsv_channels[1]);

	/**** V channel *****/

	/*** Max out V channel ***/
	cv::threshold(hsv_channels[2], hsv_channels[2], 0, 255, CV_THRESH_BINARY);

	/*** Output ***/
	cv::merge(hsv_channels, dest_image);
	cv::cvtColor(dest_image, dest_image, CV_HSV2BGR);
}