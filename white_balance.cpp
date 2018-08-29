#include "stdafx.h"
#include "calc_bound.h"
#include "opencv2/opencv.hpp"

#include <string>


using namespace std;
using namespace cv;


/*** public method ***/
void FixWhiteBalance(const Mat src_image, Mat& dest_image)
{
	/*** Divide RGB Channels ***/
	vector<Mat> channels;
	cv::split(src_image, channels);

	float mean_intensity = cv::mean(src_image.reshape(1))[0];
	// This parameter has more room for improvement
	float portion = mean_intensity * mean_intensity / 120000.0;

	// For performance reason, calculate them first:
	const int num_bins = 256;
	const int num_pixels = src_image.rows * src_image.cols;	// Make sure this number is equal to the number of bins in histogram
	const int histSize[] = { num_bins, num_pixels };
	const float range[] = { 0, 255 };
	const float* ranges[] = { range, range, range };
	const int channel_to_calc[] = { 0 };
	
	for (int i = 0; i < 3; i++)
	{
		/*** Calculating (channel's) histogram ***/
		Mat hist;
		cv::calcHist(&channels[i], 1, channel_to_calc, Mat(),
			hist, 1, histSize, ranges,
			true, false);

		/*** Get lower/upper bound of original image from histogram ***/
		uchar lower_bound = CalcLowerBound(hist, num_pixels, portion);
		uchar higher_bound = CalcUpperBound(hist, num_pixels, portion);

		float scale_factor = (255.0 / (higher_bound - lower_bound));

		/*** Expanding histogram ***/
		cv::subtract(channels[i], lower_bound, channels[i]);
		cv::multiply(channels[i], scale_factor, channels[i]);
	}

	cv::merge(channels, dest_image);

}