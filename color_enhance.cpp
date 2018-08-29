#pragma once

#include "stdafx.h"
#include "calc_bound.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void EnhanceColor(const Mat src_image, Mat& dest_image, float portion) {

	Mat src_image_hsv;
	cv::cvtColor(src_image, src_image_hsv, CV_BGR2HSV);
	vector<Mat> hsv_channels;
	cv::split(src_image_hsv, hsv_channels);

	const int num_bins = 256;
	const int num_pixels = src_image.rows * src_image.cols;	// ヒストグラムの全ビンの合計値と同じ
	const int histSize[] = { num_bins, num_pixels };
	const float range[] = { 0, 255 };
	const float* ranges[] = { range, range, range };
	const int channel_to_calc[] = { 0 };

	/**** Sチャネル *****/
	/*** ヒストグラム計算 ***/
	Mat hist;
	cv::calcHist(&hsv_channels[1], 1, channel_to_calc, Mat(),
		hist, 1, histSize, ranges,
		true, false);

	/*** ヒストグラムから上界と下界を求める ***/
	uchar lower_bound = CalcLowerBound(hist, num_pixels, portion);
	uchar higher_bound = CalcUpperBound(hist, num_pixels, portion);

	float scale_factor = (255.0 / (higher_bound - lower_bound));

	cv::subtract(hsv_channels[1], lower_bound, hsv_channels[1]);
	cv::multiply(hsv_channels[1], scale_factor, hsv_channels[1]);

	/**** Vチャネル *****/
	/*** ヒストグラム計算 ***/
	cv::calcHist(&hsv_channels[2], 1, channel_to_calc, Mat(),
		hist, 1, histSize, ranges,
		true, false);

	/*** 明るさ調整 ***/
	cv::threshold(hsv_channels[2], hsv_channels[2], 0, 255, CV_THRESH_BINARY);

	/*** 出力 ***/
	cv::merge(hsv_channels, dest_image);
	cv::cvtColor(dest_image, dest_image, CV_HSV2BGR);
}