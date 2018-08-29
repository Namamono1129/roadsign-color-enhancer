#include "stdafx.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

uchar CalcLowerBound(const Mat hist, const int sum_hist, float bound_portion)
{
	int accumulated_sum_frequency = 0;
	for (int i = 0; i < 255; i++)
	{
		accumulated_sum_frequency += hist.at<float>(i);
		float accumulated_proportion = float(accumulated_sum_frequency) / float(sum_hist);

		if (accumulated_proportion > bound_portion)
		{
			return i;
		}
	}
}

uchar CalcUpperBound(const Mat hist, const int sum_hist, float bound_portion)
{
	int accumulated_sum_frequency = 0;
	for (int i = 255; i > 0; i--)
	{
		accumulated_sum_frequency += accumulated_sum_frequency += hist.at<float>(i);
		float accumulated_proportion = float(accumulated_sum_frequency) / float(sum_hist);

		if (accumulated_proportion > bound_portion)
		{
			return i;
		}
	}
}