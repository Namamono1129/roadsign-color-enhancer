#pragma once
#include "opencv2/opencv.hpp"

using namespace cv;

void EnhanceColor(const Mat src_image, Mat& dest_image, float portion);