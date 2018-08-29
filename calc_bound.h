#pragma once

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

uchar CalcLowerBound(const Mat hist, const int sum_hist, float bound_portion);
uchar CalcUpperBound(const Mat hist, const int sum_hist, float bound_portion);