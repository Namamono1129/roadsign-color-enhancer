#include "stdafx.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

uchar CalcLowerBound(const Mat hist, const int sum_hist, float bound_portion)
{
	int accumulated_frequency = 0;
	for (int i = 0; i < 255; i++)
	{
		accumulated_frequency += hist.at<float>(i);
		float accumulated_percentage = float(accumulated_frequency) / float(sum_hist);

		/*if (accumulated_frequency > 0) {
		cout << "intensity[" << i << "] accum:" << accumulated_frequency << "(" << accumulated_percentage * 100 << "%)" << endl;
		}*/

		if (accumulated_percentage > bound_portion)
		{
			return i;
		}
	}
}

uchar CalcUpperBound(const Mat hist, const int sum_hist, float bound_portion)
{
	int accumulated_frequency = 0;
	for (int i = 255; i > 0; i--)
	{
		accumulated_frequency += accumulated_frequency += hist.at<float>(i);
		float accumulated_percentage = float(accumulated_frequency) / float(sum_hist);
		//cout << "accum:" << accumulated_frequency << "(" << accumulated_percentage * 100 << "%)" << endl;

		if (accumulated_percentage > bound_portion)
		{
			return i;
		}
	}
}